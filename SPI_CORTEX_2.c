#include<lpc17xx.h>

void spi_ini()
{
	LPC_GPIO0->FIODIR2|=(1<<0);																				// Set the SSEL bit as output.
	LPC_PINCON->PINSEL0|=(1<<30)|(1<<31);
	LPC_PINCON->PINSEL1|=(1<<4)|(1<<5);
	LPC_SPI->SPCR|=(1<<5)|(1<<6)|(1<<11);
	LPC_SPI->SPCCR=0X10;
}

void delay(unsigned int de)
{
	for(int i=0;i<=de;i++)
	{
		for(int j=0;j<=de;j++);
	}
}

int main()
{
	spi_ini();
	while(1)
	{
	LPC_GPIO0->FIOSET2|=(1<<0);
	LPC_SPI->SPDR=0XAA;
	while(!(LPC_SPI->SPSR & (1<<7)));
	delay(10000);
	LPC_GPIO0->FIOCLR2|=(1<<0);
		
	LPC_GPIO0->FIOSET2|=(1<<0);
	LPC_SPI->SPDR=0X55;
	while(!(LPC_SPI->SPSR & (1<<7)));
	delay(10000);
	LPC_GPIO0->FIOCLR2|=(1<<0);
	}
}
