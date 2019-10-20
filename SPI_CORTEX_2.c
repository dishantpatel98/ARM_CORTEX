#include "lpc17xx.h"
#include "system_LPC17xx.h"

int main(void)
{
	int i, j;
	LPC_PINCON->PINSEL0 |= (1<<31)|(1<<30);//clock for 
	LPC_PINCON->PINSEL1 |= (1<<5)|(1<<4);//mosi
	LPC_GPIO0->FIODIR2 |= (1<<0);
/* IN  lpc2148 we have 60mhz........ and in lpc1768 we have 100mHZ 
	-->For each and every block we can set different frequency
	*/
	
	
	LPC_SPI->SPCR = 0x00;  //SPCR=SPI CONTROL REGISTER
	LPC_SPI->SPCR |= (1<<5);  //MASTER Mode
	LPC_SPI->SPCCR	 = 0x10;   // THis Register indicates that master pf SPI Peripheral clock cycles that makes up an spi clock

	while(1)
	{
		
    //LPC_GPIO0->FIOCLR2 |= (1<<0);
		LPC_GPIO0->FIOSET2 |= (1<<0);     //HIGH PULSE
		LPC_SPI->SPDR = 0xff;

		while(!(LPC_SPI->SPSR)&(1<<7));//SPSR=SPI STATUS REGISTER

		for(i=0;i<10000;i++)
			for(j=0;j<50;j++);

		LPC_GPIO0->FIOCLR2 |= (1<<0); //PULSE AGAIN AFTER DATA
    LPC_GPIO0->FIOSET2 |= (1<<0);
	   	LPC_SPI->SPDR = 0x00;


		while(!(LPC_SPI->SPSR)&(1<<7));		

		for(i=0;i<10000;i++)
			for(j=0;j<50000;j++);

		LPC_GPIO0->FIOCLR2 |= (1<<0);
	  //LPC_GPIO0->FIOSET2 |= (1<<0);     HIGH PULSE
	}
}
