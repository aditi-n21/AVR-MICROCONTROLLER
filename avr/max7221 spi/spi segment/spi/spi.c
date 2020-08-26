


#include <avr/io.h>
#define MOSI PB5
#define  SCK PB7
#define SS PB4
void execute(unsigned char cmd, unsigned char dat);
void execute(unsigned char cmd, unsigned char dat)
{
	PORTB&=~(1<<SS);
	SPDR=cmd;
	while(!(SPSR&(1<<SPIF)));
	
	SPDR=dat;
	while(!(SPSR&(1<<SPIF)));
	PORTB|=(1<<SS);
	
}
int main(void)
{
	DDRB|=(1<<MOSI)|(1<<SCK)|(1<<SS);
SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
	
	while(1)
	{	
		execute(0x09, 0b00000011);
		execute(0x0B, 0x02);
		execute(0x0C, 0x01);
		execute(0x01, 0x07);
		execute(0x02, 0x05);
	}		
}