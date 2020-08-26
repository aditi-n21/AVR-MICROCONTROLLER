
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{
	DDRB&=~(1<<PB2);
	DDRB&=~(1<<PB3);
	//DDRA&=~(1<<PA0);
	//DDRA&=~(1<<PA1);
	//PORTA|=(1<<PA0)|(1<<PA1);
	DDRD=0x07;
	ACSR=0x00;       //to set ACO as zero
	ADCSRA&=~(1<<ADEN);
    while(1)
    {
         SFIOR|=(1<<ACME);
		 ADMUX=0x00;
		 _delay_us(1);
		 if(bit_is_set(ACSR,ACO))
			PORTD|=(1<<PD0);
		else
			PORTD&=~(1<<PD0);
			
		 SFIOR|=(1<<ACME);
		 ADMUX=0x01;	// ADC1 channel is selected
		 _delay_us(1);
		 if(bit_is_set(ACSR,ACO))
		 PORTD|=(1<<PD1);
		 else
		 PORTD&=~(1<<PD1);		
		 
		  SFIOR&=~(1<<ACME);
		  //ADMUX=0x00;
		  _delay_us(1);
		  if(bit_is_set(ACSR,ACO))
		  PORTD|=(1<<PD2);
		  else
		  PORTD&=~(1<<PD2);
    }
}