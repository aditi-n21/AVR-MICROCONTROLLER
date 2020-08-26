
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
void int_interrupt0();
void car_trun();
void car_trun()
{
	if (bit_is_set(PIND,PD3))
	{
		PORTA=0x55;
		_delay_ms(900);
			PORTA=0xa20;
			_delay_ms(900);
				PORTA=0xaa;
				_delay_ms(900);
	}
}
void int_interrupt0()
  {
      if (bit_is_set(PIND,PD2))
    {
	    cli();
	    GICR=(1<<INT0);
	    MCUCR=(1<<ISC00);
	    sei();
	}
}
ISR(INT0_vect)
{
	    PORTC=0x20;
	    _delay_ms(900);
	    PORTC=0xaa;
	    _delay_ms(900);  
   car_trun();
        PORTC=0x02;
        _delay_ms(900);

        PORTC=0x0aa;
       _delay_ms(900);

        PORTC=0x02;
       _delay_ms(900);
       PORTC=0x0aa;
       _delay_ms(900);

       PORTC=0x20;
       _delay_ms(900);

}

int main(void)
 {    DDRA=0xff;
   	  DDRB=0x00;
	  DDRD&=~(1<<PD2)|(1<<PD3);
	  PORTB|=(1<<PB0)|(1<<PB1)|(1<<PB2)|(1<<PB3);
      PORTD&=~((1<<PD2)|(1<<PD3));
	  DDRC=0xff;
	  _delay_ms(1000);
	  _delay_ms(1000);
	   
	
while(1)
   {
      if (bit_is_clear(PINB,PB0)) //for forwared
		   {
			   PORTC=0xaa;
			   _delay_ms(500);
		   }			    		  
		   int_interrupt0(); 	 		   		   
     if(bit_is_clear(PINB,PB1)) //for revers 
           {
			   PORTC=0x55;
			   _delay_ms(500);
		   }		   		   
     if (bit_is_clear(PINB,PB2))   // for right turan
           {
	      	  PORTC=0x20;
			 _delay_ms(500);
	       }
     if(bit_is_clear(PINB,PB3))    // for left turan 
          {
	          PORTC=0x02;
			_delay_ms(500);
	      }	          
else
  {
        PORTC=0x00;
	} 
  }	   
}