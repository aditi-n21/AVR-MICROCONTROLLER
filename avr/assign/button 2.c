/*
 * button_2.c
 *
 * Created: 8/26/2015 4:18:32 PM
 *  Author: DELL_PC
 */ 


#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB&=~((1<<PB0)|(1<<PB1));
	DDRC=0xff;
	PORTB=0xff;
	unsigned char j=0, arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
    while(1)
    {
         if (bit_is_clear(PINB,PB0))
         { while(bit_is_clear(PINB,PB0));
			 j++;
			 if (j>9)
			 {
				 j=0;
			 }
			 
         } 
         else if (bit_is_clear(PINB,PB1))
         {
			 while(bit_is_clear(PINB,PB1));
			 if (j>0)
			 {
				 j--;
			 }
			 else
			 {
			 j=9;
			 }
         }
		 else
		 {
			 PORTC=arr[j];
			 _delay_ms(100);
			  
		 }
}
	}