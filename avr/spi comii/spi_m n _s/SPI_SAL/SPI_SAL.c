
#include <avr/io.h>
#define MISO 6
int main(void)
{ DDRB|=(1<<MISO);
	DDRA=0xff;
	SPCR|=(1<<SPE);
	while(1)
	{
		SPDR=0x23;
		while(!(SPSR&(1<<SPIF)));
		PORTA=SPDR;
		
	}
}