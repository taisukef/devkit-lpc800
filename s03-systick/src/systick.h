typedef struct {
	__I uint32 RESERVED0;
	__I uint32 RESERVED1;
	__I uint32 RESERVED2;
	__I uint32 RESERVED3;
	__IO uint32 CSR;
	__IO uint32 RVR;
	__IO uint32 CVR;
	__IO uint32 CALIB;
} SYSTICK_TypeDef;
#define SYST ((SYSTICK_TypeDef*)0xE000E000)

#define SYST_CSR_ENABLE (1UL << 0)
#define SYST_CSR_TICKINT (1UL << 1)
#define SYST_CSR_CLKSOURCE (1UL << 2)
#define SYST_CSR_COUNTFLAG (1UL << 16)

volatile uint32 systick_cnt = 0;

void systick_init() {
	NVIC_DisableIRQ(SysTick_IRQn);
	systick_cnt = 0;
	SYST->RVR = __MAIN_CLOCK / 1200 - 1; // msec
	SYST->CVR = 0;
	NVIC_EnableIRQ(SysTick_IRQn);
	SYST->CSR |= SYST_CSR_ENABLE | SYST_CSR_TICKINT | SYST_CSR_CLKSOURCE;
}

void SysTick_Handler(void) {
	systick_cnt++;
}

void systick_delay(uint32 ms) {
	uint32 cnt = systick_cnt + ms;
	while (systick_cnt < cnt);
}
