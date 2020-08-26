/*
 * dtmf_robo.c
 *
 * Created: 10/10/2014 10:48:04 AM
 *  Author: what
 */ 


#include <avr/io.h>
#include<util/delay.h>
#define sense PINB
#define sense_ddr DDRB
int main(void)
{DDRD=0xff;
	sense_ddr&=0xf0;
	unsigned char input;
	
    while(1)
    {  
		input=sense;
		input=input & 0x0f;
        switch(input)
		   {
			   case 0x01:   
			   PORTD=0x01;
			              _delay_ms(100);
						  break;
				case 0x02:
				PORTD=0x02;
				  _delay_ms(100);
							break;
				case 0x04:
				PORTD=0x04;
				 _delay_ms(100);
						   break;					  
			    case 0x08:
				PORTD=0x08;
				 _delay_ms(100);          
							break;
				case 0x06:
				PORTD=0x06;
				 _delay_ms(100);					   
						   break;
						   
						   case 0x05:
						   PORTD=0x05;
						   _delay_ms(100);
						   break;
						   
						   case 0x07:
						   PORTD=0x07;
						   _delay_ms(100);
						   break;
				default:
				           break;		   
		   }		   
		   
    }
}
