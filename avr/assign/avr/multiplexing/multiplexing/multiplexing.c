/*
 * multiplexing.c
 *
 * Created: 08-02-2013 17:12:10
 *  Author: kaisar
 */ 

#include<avr/io.h>
#include<util/delay.h>
#define seg1 PB0
#define seg2 PB1

int main(void)
{
	DDRB=0x03;
	DDRD=0xff;
	PORTB=0x00;
//	PORTD=0xff;
	 unsigned char a[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
		 unsigned char i,j;
		 
	 while(1)
    {   
		for (i=0;i<10;i++)
		{
			
			for (j=0;j<10;j++)
			{
				PORTB|=(1<<seg1);
				PORTD=a[i];
				_delay_ms(50);
				PORTB&=~(1<<seg1);
				PORTB|=(1<<seg2);						
				PORTD=a[j];
						_delay_ms(200);
		
			}
		}    
           
	      }
}