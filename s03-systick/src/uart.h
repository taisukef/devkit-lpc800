#define UARTCLKDIV (*(__IO uint32*)(0x40048094))
#define UARTFRGDIV (*(__IO uint32*)(0x400480F0))
#define UARTFRGMULT (*(__IO uint32*)(0x400480F4))

#define UART_ENABLE          (1 << 0)
#define UART_DATA_LENGTH_8   (1 << 2)
#define UART_PARITY_NONE     (0 << 4)
#define UART_STOP_BIT_1      (0 << 6)

/* Status bits */
#define UART_STATUS_RXRDY    (1 << 0)
#define UART_STATUS_RXIDLE   (1 << 1)
#define UART_STATUS_TXRDY    (1 << 2)
#define UART_STATUS_TXIDLE   (1 << 3)
#define UART_STATUS_CTSDEL   (1 << 5)
#define UART_STATUS_RXBRKDEL (1 << 11)

typedef struct {
	__IO uint32 CFG;
	__IO uint32 CTRL;
	__IO uint32 STAT;
	__IO uint32 INTENSET;
	__O uint32 INTENCLR;
	__I uint32 RXDATA;
	__I uint32 RXDATASTAT;
	__IO uint32 TXDATA;
	__IO uint32 BRG;
	__I uint32 INTSTAT;
} UART_TypeDef;
#define UART0 ((UART_TypeDef*)0x40064000)
#define UART1 ((UART_TypeDef*)0x40068000)
#define UART2 ((UART_TypeDef*)0x4006C000)

void uart0_init(uint32 bps);
void uart0_putc(char c);
void uart0_puts(char *s, uint32 len);

void uart0_init(uint32 bps) {
	PINASSIGN0 = 0xffff0004UL; // UART0 - CTS:none RTS:none RXD:0 TXD:4
	
	NVIC_DisableIRQ(UART0_IRQn);
	SYSAHBCLKCTRL |= SYSAHBCLKCTRL_UART0;
	
	const uint32 CLKDIV = 1;
	UARTCLKDIV = CLKDIV;
	
	PRESETCTRL &= ~PRESETCTRL_UART0;
	PRESETCTRL |= PRESETCTRL_UART0;

	uint32 clk = __MAIN_CLOCK / CLKDIV;
	UART0->CFG = UART_DATA_LENGTH_8 | UART_PARITY_NONE | UART_STOP_BIT_1;
	UART0->BRG = clk / 16 / bps - 1;
	UARTFRGDIV = 0xFF;
	UARTFRGMULT = (((clk / 16) * (UARTFRGDIV + 1)) / (bps * (UART0->BRG + 1))) - (UARTFRGDIV + 1);

	UART0->STAT = UART_STATUS_CTSDEL | UART_STATUS_RXBRKDEL; // clear status bits
	NVIC_EnableIRQ(UART0_IRQn);
	UART0->CFG |= UART_ENABLE; // enable
}
void uart0_putc(char c) {
	while (!(UART0->STAT & UART_STATUS_TXRDY)); // Wait until ready to send
	UART0->TXDATA = c;
}
void uart0_puts(char *s, uint32 len) {
	while (len > 0) {
		uart0_putc(*s);
		s++;
		len--;
	}
}
