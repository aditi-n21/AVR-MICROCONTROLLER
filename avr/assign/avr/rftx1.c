#include<avr/io.h>
void main()
{
DDRB=0xff;
DDRD=0xff;
DDRA=0x00;
ADCSRA=0x87;
ADMUX=0xc0;

while(1)
{
ADCSRA |= (1<<ADSC);
while((ADCSRA & (1<<ADIF))==0);
PORTB=ADCL;
PORTD=ADCH;
}
}
