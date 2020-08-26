/*
 * first_qestion.c
 *
 * Created: 8/19/2015 10:29:31 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	unsigned int i;
	DDRB=0xFF;
    
    
		for(i=0;i<256;i++)
		{
		PORTB=i;
		_delay_ms(3000);
		
        //TODO:: Please write your application 
}
}