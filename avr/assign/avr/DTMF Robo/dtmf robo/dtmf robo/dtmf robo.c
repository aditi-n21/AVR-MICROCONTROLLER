/*
 * dtmf_robo.c
 *
 * Created: 10/10/2014 10:48:04 AM
 *  Author: what
 */ 


#include <avr/io.h>
#include<util/delay.h>
#define motor PORTC
#define motor_ddr DDRC
#define mot1_a PC0
#define mot1_b PC1
#define mot1_c PC2
#define mot1_d PC3
#define sense PINB
#define sense_ddr DDRB
int main(void)
{
	sense_ddr&=0xf0;
	motor_ddr|=0x0f;
	unsigned char input;
	
    while(1)
    {  
		input=sense;
		input=input & 0x0f;
        switch(input)
		   {
			   case 0x02:   
			              PORTC|=(1<<mot1_a);
			              PORTC&=~(1<<mot1_b);
			              PORTC|=(1<<mot1_c);
			              PORTC&=~(1<<mot1_d);
			              _delay_ms(100);
						  break;
				case 0x04:
				            PORTC|=(1<<mot1_a);
				            PORTC&=~(1<<mot1_b);
				            PORTC|=(1<<mot1_c);
				            PORTC|=(1<<mot1_d);
				            _delay_ms(100);
							break;
				case 0x06:
				           PORTC|=(1<<mot1_a);
				           PORTC|=(1<<mot1_b);
				           PORTC|=(1<<mot1_c);
				           PORTC&=~(1<<mot1_d);
				           _delay_ms(100);
						   break;					  
			    case 0x08:
				           PORTC&=~(1<<mot1_a);
				           PORTC|=(1<<mot1_b);
				           PORTC&=~(1<<mot1_c);
				           PORTC|=(1<<mot1_d);
				           _delay_ms(100);          
							break;
				case 0x05:
				           PORTC|=(1<<mot1_a);
				           PORTC|=(1<<mot1_b);
				           PORTC|=(1<<mot1_c);
				           PORTC|=(1<<mot1_d);
				           _delay_ms(100);					   
						   break;
				default:
				           break;		   
		   }		   
		   
    }
}
