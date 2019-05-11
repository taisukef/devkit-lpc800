#include "stddef.h"
#include "vectors.h"
#include "lpc810.h"
#include "core_cm0.h"
#include "uart.h"

extern uint32 __data_section_table;

static inline void c_init() {
	// clear RAM
	memclear((uint8*)SRAM_LOC, SRAM_LEN);
	
	// copy init value to RAM
	uint* ad = &__data_section_table;
	memcopy((uint8*)SRAM_LOC, (uint8*)ad[0], ad[1]);
}

// 12MHz
static int WAIT_CNT = 1200000 / 2 / 10;

void Reset_Handler(void) {
	c_init();
	
	/*
	PIO0_5 PIO0_0
	PIO0_4 GND
	PIO0_3 VDD
	PIO0_2 PIO0_1
	*/
	
	SYSAHBCLKCTRL |= SYSAHBCLKCTRL_GPIO | SYSAHBCLKCTRL_SWM | SYSAHBCLKCTRL_IOCON;
	FLASHCFG &= ~3; // no wait
	
	PINENABLE0 = 0xFFFFFFBFUL; // enable reset
	GPIO_DIR0 |= 0b1100; // PIO0_2, PIO0_3
	
	uart0_init(115200);
//	GPIO_SET0 |= 0b100; // PIO0_2
	
	int ch = '*';
	for (;;) {
		int n = uart0_getc();
		if (n >= 0) {
			ch = n;
		}
		uart0_putc(ch);
		GPIO_NOT0 |= 0b100; // PIO0_2
		for (volatile int i = 0; i < WAIT_CNT; i++); // 2clock?
	}
}
