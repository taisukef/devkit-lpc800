#include "stddef.h"
#include "vectors.h"
#include "lpc810.h"
#include "systick.h"

extern unsigned int __data_section_table;

static inline void c_init() {
	// clear RAM
	memclear((uint8*)SRAM_LOC, SRAM_LEN);
	
	// copy init value to RAM
	uint* ad = &__data_section_table;
	memcopy((uint8*)SRAM_LOC, (uint8*)ad[0], ad[1]);
}

const char WS2812B_DRIVER[] = {
	0x30, 0xB5, 0x72, 0xB6, 0x0F, 0x4C, 0x04, 0x22, 0x80, 0x25, 0x0B, 0x78, 0x22, 0x60, 0x2B, 0x42,
	0x08, 0xD0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x22, 0x60, 0x07, 0xE0, 0x00, 0x00, 0x22, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x6D, 0x08, 0xE9, 0xD1, 0x49, 0x1C, 0x01, 0x38, 0xE4, 0xD1, 0x62, 0xB6,
	0x30, 0xBD, 0x00, 0x00, 0x00, 0x23, 0x00, 0xA0
};
/*
https://ichigojam.github.io/asm15/

'WS2812B driver
'param
'	R0 - data count (ex WS2812B x 3) == 3
'	R1 - address (G, R, B)
'use
'	R2 - OUT value
'	R3 - data value
'	R4 - GPIO address
'	R5 - bit count
@WS2812B
	PUSH {R4,R5,LR}
	CPSID
	R4=[@GPIO_NOT0]L
	R2=`100 ' PIO0_2
	
@LOOP_DATA
	R5=#80
	R3=[R1]
@LOOP_BIT
	[R4]L=R2
	R3&R5
	IF 0 GOTO @ZERO
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
	[R4]L=R2
	GOTO @JOIN
@ZERO
	NOP
	[R4]L=R2
	NOP
	NOP
	NOP
	NOP
	NOP
	NOP
@JOIN
	R5=R5>>1
	IF !0 GOTO @LOOP_BIT
	
	R1=R1+1 '+6clock
	R0-=1
	IF !0 GOTO @LOOP_DATA
	CPSIE
	POP {R4,R5,PC}

@GPIO_NOT0
	DATA L #A0002300
*/
//typedef void (*FUNC_WS2812B_WRITE)(int, char*);
typedef void (*FUNC_WS2812B_WRITE)();
FUNC_WS2812B_WRITE ws2812b_write = (FUNC_WS2812B_WRITE)(WS2812B_DRIVER + 1);

const char GPIO_TOGGLE[] = {
//	0x00, 0xB5, 0x02, 0x48, 0x04, 0x21, 0x01, 0x60, 0x00, 0xBD, 0x00, 0x00, 0x00, 0x23, 0x00, 0xA0,
	0x01, 0x48, 0x04, 0x21, 0x01, 0x60, 0x70, 0x47, 0x00, 0x23, 0x00, 0xA0
};
typedef void (*FUNC_GPIO_TOGGLE)();
FUNC_GPIO_TOGGLE gpio_toggle = (FUNC_GPIO_TOGGLE)(GPIO_TOGGLE + 1);
/*
'WS2812B driver
	R0=[@GPIO_NOT0]L
	R1=`100 ' PIO0_2
	[R0]L=R1
	RET
@GPIO_NOT0
	DATA L #A0002300
*/

static inline int btn() {
	return !GPIO_PBYTE0[3];
}

// 12MHz
static inline void wait(int n) { // wait n * 2 cycles
	for (volatile int i = 0; i < n; i++);
}

int start();

#define N_LED 21
uint8 data[N_LED * 3];

void Reset_Handler(void) {
	c_init();

	// clock 12MHz
	FLASHCFG &= ~3; // Flash no wait
	
	/*
	PIO0_5(RESET) PIO0_0(TXD)
	PIO0_4(TXD)   GND
	PIO0_3        VDD
	PIO0_2        PIO0_1(ISP) - 外部pullup合ったほうがいい
	*/
	
	SYSAHBCLKCTRL |= SYSAHBCLKCTRL_GPIO | SYSAHBCLKCTRL_SWM | SYSAHBCLKCTRL_IOCON;
	PINENABLE0 = 0xFFFFFFBF;
	
	systick_init();

	GPIO_DIR0 |= 0b0100; // out:PIO0_2, in:PIO0_3
	start(N_LED);
	for (;;);
}

void flush() {
	ws2812b_write(N_LED * 3, data);
}

uint32 m = 83103851;
int rnd(int n) {
	m = m * 5 + 1;
	return m % n;
}
void set(int n, int col) {
	n *= 3;
	data[n] = (col >> 8) & 0xff; // G
	data[n + 1] = (col >> 16) & 0xff; // R
	data[n + 2] = col & 0xff; // B
}
int rgb(int r, int g, int b) {
	return (r << 16) | (g << 8) | b;
}
int get(int n) {
	n *= 3;
	return (data[n] << 8) | (data[n + 1] << 16) | data[n + 2]; // G R B -> RGB
}
void clear() {
	for (int i = 0; i < N_LED * 3; i++)
		data[i] = 0;
}
int hsv2rgb(int h, int s, int v) { // h:0-360, s:0-100, v:0-100
	int r = v;
	int g = v;
	int b = v;
	if (s > 0) {
		int d = h / 60 % 6;
		int c = v - (59 - h % 60) * v / 60 * s / 100;
		int e = v - h % 60 * v / 60 * s / 100;
		int f = v * (100 - s) / 100;
		switch (d) {
			case 0: g = c; b = f; break;
			case 1: r = e; b = f; break;
			case 2:	r = f; b = c; break;
			case 3: r = f; g = e; break;
			case 4: r = c; g = f; break;
			case 5: g = f; b = e; break;
		}
	}
	return rgb(r, g, b);
}
void rotate(int dir) {
	if (dir == 0) {
		uint8 n1 = data[N_LED * 3 - 3];
		uint8 n2 = data[N_LED * 3 - 2];
		uint8 n3 = data[N_LED * 3 - 1];
		for (int i = N_LED * 3 - 4; i >= 0; i--)
			data[i + 3] = data[i];
		data[0] = n1;
		data[1] = n2;
		data[2] = n3;
	} else {
		uint8 n1 = data[0];
		uint8 n2 = data[1];
		uint8 n3 = data[2];
		for (int i = 3; i < N_LED * 3; i++)
			data[i - 3] = data[i];
		data[N_LED * 3 - 3] = n1;
		data[N_LED * 3 - 2] = n2;
		data[N_LED * 3 - 1] = n3;
	}
}

