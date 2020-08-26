/*
 * second.c
 *
 * Created: 8/19/2015 11:00:34 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	unsigned char i, arr[10]="012345ABCD";
	DDRB=0xFF;
    while(1)
    {
		for(i=0;i<10;i++)
		{
        PORTB=arr[i];
		_delay_ms(1000);//TODO:: Please write your application code 
    }
	}	
}