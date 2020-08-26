/*
 * fourth_ques.c
 *
 * Created: 8/19/2015 11:25:54 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	signed int i;
	unsigned char arr[9]={'-4','-3','-2','-1','0','1','2','3','4'};
		DDRB=0xFF;
	    for(i=0;i<9;i++)
    {
		PORTB=arr[i];
		_delay_ms(500);
        //TODO:: Please write your application code 
    }
}