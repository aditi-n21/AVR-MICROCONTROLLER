/*
 * spi_m.c
 *
 * Created: 1/25/2014 10:47:15 AM
 *  Author: MANOJ
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define MOSI 5
#define SCK 7
#define MISO 6
int main(void)
{
	//unsigned char i,arr[]="ABCDEF";
	DDRB|=(1<<MOSI)|(1<<SCK)|(1<<PB4);
	DDRB&=~(1<<MISO);
	DDRA=0xff;
	SPCR|=(1<<SPE)|(1<<MSTR)|(1<<SPR0);
    while(1)
    {
         SPDR=0x00;
		// _delay_ms(250);
		 
		while((SPSR&(1<<SPIF))==0);
		// _delay_ms(250);
		  PORTA=SPDR;
	 while(1);
		  
		 /*for(i=0;i<6;i++)
		 {
			 SPDR=arr[i];
		 _delay_us(2);
		 while(!(SPSR&(1<<SPIF)));
		 _delay_us(20);
		 PORTA=SPDR;
		 }		 */
    }
	while(1);
	//return 0;
}