#include "stddef.h"
#include "vectors.h"
#include "lpc810.h"

extern unsigned int __data_section_table;

static inline void c_init() {
	// clear RAM
	memclear((uint8*)SRAM_LOC, SRAM_LEN);
	
	// copy init value to RAM
	uint* ad = &__data_section_table;
	memcopy((uint8*)SRAM_LOC, (uint8*)ad[0], ad[1]);
}

// 12MHz
static int WAIT_CNT = 1200000 / 2;

void Reset_Handler(void) {
	c_init();
	
	/*
	PIO0_5(RESET) PIO0_0(TXD)
	PIO0_4(TXD)   GND
	PIO0_3        VDD
	PIO0_2        PIO0_1(ISP)
	*/
	
	SYSAHBCLKCTRL |= SYSAHBCLKCTRL_GPIO | SYSAHBCLKCTRL_IOCON;
	FLASHCFG &= ~3; // no wait
	
	PINENABLE0 = 0xFFFFFFBF;
	
	GPIO_DIR0 |= 0b1100; // PIO0_2, PIO0_3
	
	for (;;) {
		GPIO_NOT0 |= 0b100; // PIO0_2
		for (volatile int i = 0; i < WAIT_CNT; i++); // 2clock?
	}
}
