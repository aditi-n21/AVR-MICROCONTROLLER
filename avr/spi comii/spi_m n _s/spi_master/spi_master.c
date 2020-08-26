
#include <avr/io.h> 
#include <util/delay.h>
#define MOSI 5
#define SCK 7
//#define ss1 PC0
//#define  ss2 PC1
int main(void)
{ DDRB|=((1<<MOSI)|(1<<SCK));
	//DDRA=0xff;
	DDRC|= ((1<<PC1)|(1<<PC0));
	SPCR|=((1<<SPE)|(1<<SPR0)|(1<<MSTR));
    while(1)
    {  PORTC|=(1<<PC0);
		 PORTC&=~(1<<PC1);
		SPDR=0x07;
		while(!(SPSR&(1<<SPIF)));
		PORTA=SPDR;
		PORTC|=(1<<PC1);
		PORTC&=~(1<<PC0);
    SPCR|=(1<<SPE);
	 SPDR=0x6f;
     while(!(SPSR&(1<<SPIF)));
     PORTA=SPDR;
    }
}