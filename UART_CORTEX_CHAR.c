#include "lpc17xx.h"
#include "system_LPC17xx.h"

int main(void)
{
	SystemInit();
char x;
	LPC_PINCON->PINSEL0 |= (1<<4)|(1<<6);
	LPC_SC->PCLKSEL0 |= (0<<7)|(0<<6);
	LPC_UART0->LCR |= (1<<0)|(1<<1);
	LPC_UART0->LCR |= (1<<7);

	LPC_UART0->DLL = 152;	
	LPC_UART0->DLM |=0X00;
	LPC_UART0->LCR &= ~(1<<7);
	LPC_UART0->FDR |= (1<<4);
	LPC_UART0->TER |= (1<<7);

	while(1)
	{
		while(!(LPC_UART0->LSR&(1<<0)));
		x = LPC_UART0->RBR;
		while(!(LPC_UART0->LSR&(1<<5)));
		LPC_UART0->THR = x;
	}
	return 0;
}