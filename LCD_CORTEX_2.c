#include <lpc17xx.h>
#include "C:\Users\DESD\Documents\ARM_PROGRAMS\lcd.h"	
	
int main(void)
{
	init_lcd();
	send_cmd(0x80);
	user_string("CDAC");
	send_cmd(0xc0);
	user_string("ACTS");
}