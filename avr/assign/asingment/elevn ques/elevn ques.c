/*
 * elevn_ques.c
 *
 * Created: 8/21/2015 8:59:29 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include<util/delay.h>
int main(void)
{
	DDRC&=~(1<<PC5);
	DDRB=0xFF;
    while(1)
    {
     //if(bit_is_set(PINC.PC5))   
	  if(PINC&(1<<PC5))
	  {
		  PORTB=0x00;
		  }          
		  else
		  {
			  PORTB=0xFF;
			  }                //or we can use  if!(pINC&(1<<PC5)) 
    }
}