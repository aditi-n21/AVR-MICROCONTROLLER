/*
 * line.c
 *
 * Created: 2/9/2015 11:06:55 AM
 *  Author: what
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB=0xff;
	DDRC=0x00;
	int ls = 0,rs=0,cs=0;
	 
    while(1)
    {
		ls = PINC && 0b0100000;
		rs = PINC && 0b0001000;
		cs = PINC && 0b0010000;
		if ((ls = 0b0100000)&(rs=0b0001000))
		{
			PORTB= 0b00001001;
		}
			
      
    }
}