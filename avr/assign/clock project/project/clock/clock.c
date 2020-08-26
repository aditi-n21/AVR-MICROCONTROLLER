#define F_CPU 4000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#define segdataport PORTB
#define segdatapin PINB
#define segdataDDR DDRB
#define segcntrlport PORTC
#define segcntrlpin PINC 
#define segcntrlDDR DDRC
unsigned char hours = 0;
unsigned char minutes = 0;
unsigned char seconds = 0;
unsigned char digitTO7segencoder(unsigned char digit, unsigned char common);
ISR(TIMER1_COMPA_vect);
int main(void)
{
	segdataDDR=0xff;
	segcntrlDDR=0x3f;
	segcntrlport=0xff;
	TCCR1B = (1<<CS12|1<<WGM12);
	OCR1A = 15625-1;
	TIMSK = 1<<OCIE1A;
	sei();
    while(1)
    {
      if ((segcntrlpin & 0x40)==0)
      {
		  _delay_ms(200);
		  if(minutes < 59)
		  minutes++;
		  else
		  minutes = 0;
      }
	  if ((segcntrlpin & 0x80)==0)
	  {
		  _delay_ms(200);
		  if(hours < 23)
		  hours++;
		  else
		  hours = 0;
	  }
	  //segdataport = digitTO7segencoder(seconds%10,1);
	  //segcntrlport = ~0x01;
	  //segdataport = digitTO7segencoder(seconds/10,1);
	 // segcntrlport = ~0x02;
	  
	  segdataport = digitTO7segencoder(minutes%10,1);
	  segcntrlport = ~0x04;
	  segdataport = digitTO7segencoder(minutes/10,1);
	  segcntrlport = ~0x08;
	  
	  segdataport = digitTO7segencoder(hours%10,1);
	  segcntrlport = ~0x10;
	  segdataport = digitTO7segencoder(hours/10,1);
	  segcntrlport = ~0x20;
    }
	return 0;
}

unsigned char digitTO7segencoder(unsigned char digit, unsigned char common)
{
	unsigned char segval;
	switch(digit)
	{
		case 0: if(common==1) segval = 0b00111111;
		        else         segval = ~0b00111111;
						break;
	    case 1: if(common==1) segval = 0b00000110;
			    else         segval = ~0b00000110;
			            break;				
	
	    case 2: if(common==1) segval = 0b01011011;
	            else         segval = ~0b01011011;
	                    break;
	
	    case 3: if(common==1) segval = 0b01001111;
	            else         segval = ~0b01001111;
	                    break;
	
	   case 4: if(common==1) segval = 0b01100110;
	           else         segval = ~0b01100110;
	                    break;
	
	   case 5: if(common==1) segval = 0b01101101;
	           else         segval = ~0b01101101;
	                    break;
	
	   case 6: if(common==1) segval = 0b01111101;
	           else         segval = ~0b01111101;
	                    break;
	
	   case 7: if(common==1) segval = 0b00000111;
	           else         segval = ~0b00000111;
	                    break;
	
	   case 8: if(common==1) segval = 0b01111111;
	           else         segval = ~0b01111111;
	                    break;
	
	  case 9: if(common==1) segval = 0b01101111;
	          else         segval = ~0b01101111;
	                    break;
	}
	return segval;
}

ISR(TIMER1_COMPA_vect)
{
	seconds++;
	if (seconds == 60)
	{
		seconds = 0;
		minutes++;
	}
	if (minutes == 60)
	{
		minutes = 0;
		hours++;
	}
	if(hours > 23)
	hours = 0;
}