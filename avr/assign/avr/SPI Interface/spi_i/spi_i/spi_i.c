/*
 * spi_i.c
 *
 * Created: 1/24/2014 10:57:22 PM
 *  Author: MANOJ
 */ 

/*
#include <avr/io.h>
#include <util/delay.h>
#define MISO 6
#define MOSI 5
#define SCK 7

//void spi_init(void);
//unsigned char spi_rx(void);
int main(void)
{
	DDRD=0xff;
//	unsigned char k;
//	PORTD=0x00;
	//spi_init();
	DDRB&=~(1<<MOSI);
	DDRB&=~(1<<SCK);
	DDRB|=(1<<MISO);
	SPCR|=(1<<SPE);
    while(1)
   {
		//PORTD=spi_rx();
		//while(!(SPSR&(1<<SPIF)));
		PORTD=SPDR;
		_delay_ms(10);
	//	while(1);
	//	SPDR='1';
	//	k=SPDR;
		
		/*switch(k)
		{
			case 'A':  
				SPDR='1';
				_delay_ms(10);
				break;
			case 'B':
				SPDR='2';
				_delay_ms(10);
				break;
			case 'C':
				SPDR='3';
				_delay_ms(10);
				break;
			case 'D':
				SPDR='4';
				_delay_ms(10);
				break;
			case 'E':
				SPDR='5';
				_delay_ms(10);
				break;
			default:
				SPDR='6';
				_delay_ms(10);
				break;					
		}
    }
}*/
/*void spi_init(void)
{
	DDRB=(1<<MISO);
	SPCR=(1<<SPE);
}	
unsigned char spi_rx(void)
{
	while(!(SPSR&(1<<SPIF)));
	return SPDR;
}
*/
// Program to SPI (serial peripheral interface) using AVR microcontroller (ATmega16)
#include<avr/io.h>
#include<util/delay.h>

#define MOSI PB5

void SPI_init();
unsigned char SPI_RX(void);

int main()
{
	
	DDRD=0xFF;
	
	
	SPI_init();
	while(1)
	{
		SPDR=0xff;
		PORTD=SPI_RX();		// move SPDR value to POTRD
	//	SPDR='A';
		while(1);
	}
	
}

void SPI_init()					//SPI initialization
{
	DDRB&=~((1<<MOSI)|(1<<PB7));			// set MOSI as output pin, rest as input
	SPCR|=(1<<SPE);			// Enable SPI
	DDRB|=(1<<PB6);
}


unsigned char SPI_RX()
{
	while(!(SPSR &(1<<SPIF)));	//wait until SPIF get high
	return SPDR;				// return SPDR value
}