/*
 * comapartor_analog.c
 *
 * Created: 8/21/2015 4:47:25 PM
 *  Author: what
 */ 


#include <avr/io.h>
#include <util/delay.h>
void main()
   {
	   DDRD|=(1<<PD0)|(1<<PD1)|(1<<PD2);
	   ACSR=0x00;
	   ADCSRA&=~(1<<ADEN);
    while(1)
	{
     SFIOR|=(1<<ACME);
	  ADMUX=0x00;
	  if(bit_is_set(ACSR,ACO))
	  {
		  PORTD|=(1<<PD0);
	  }
	  else
	  {
		  PORTD&=~(1<<PD0);
	  }	
	    ADMUX=0x01;
	  if(bit_is_set(ACSR,ACO))
	  {
		  PORTD|=(1<<PD1);
	  }
	  else
	  {
		  PORTD&=~(1<<PD1);
	  }	
	  
	 SFIOR=0x00;
	   if(bit_is_set(ACSR,ACO))
	   {
		   PORTD|=(1<<PD2);
	   }
	   else
	   {
		   PORTD&=~(1<<PD2);
	   }
	  }
	}	  	  	   
	  
	  	  	   