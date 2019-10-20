#include "lpc17xx.h"
#include "system_LPC17xx.h"

int main(void)
{
	SystemInit();//TO CONFIGURE FREQUENCY PRESCALER ETC
	
	LPC_GPIO2->FIODIR|=(1<<9)|(1<<11);  //Set the direction of the buzzer and led pins 
	                                    //led is connected to p2.9
	                                    //Buzzer is connected to p2.11
	LPC_PINCON->PINSEL4 |= (1<<24);   
	LPC_SC->EXTMODE |=(0<<2);//Edge sensitive
	LPC_SC->EXTPOLAR |=(0<<2);//Low active
	NVIC_EnableIRQ(EINT2_IRQn);
	while(1)
	{
		LPC_GPIO2->FIOCLR|=(1<<9)|(1<<11);//LED and BUZZER are ON before calling the interrupt....When we press the switch from external
		                             //interrupt inside isr we will OFF the BUZZER and LED...ISR WILL BE CALLEDi.e EXTERNAL INTERRRUPT WILL BE ACTIVE  ONLY WHEN THE SWITCH IS KEPT PRESSED
	}	
}	

void EINT2_IRQHandler(void)  //dont change isr name!
{
	LPC_SC->EXTINT |=(1<<2);
	LPC_GPIO2->FIOSET|=(1<<9)|(1<<11);
}
