/*
 * External.c
 *
 * Created: 3/13/2014 1:24:13 PM
 *  Author: MANOJ
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <string.h>

#define lcd PORTB
#define rs PD0
#define rw PD1
#define en PD2

void lcd_init(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdstr(unsigned char*);
void display(void);
unsigned int pulse;

void init_interrupts()
{
	cli();
	GICR=(1<<INT1);
	MCUCR=(3<<ISC10);
	sei();
}
void display(void)
{
	unsigned int d0,d1,d2,d3,d4;
	d0=(pulse/10000)+48;
	d1=(pulse/1000)%10+48;
	d2=(pulse/100)%10+48;
	d3=(pulse/10)%10+48;
	d4=(pulse%10)+48;
	lcdcmd(0xcb);
	lcddata(d4);
		lcdcmd(0xca);
		lcddata(d3);
			lcdcmd(0xc9);
			lcddata(d2);
				lcdcmd(0xc8);
				lcddata(d1);
					lcdcmd(0xc7);
					lcddata(d0);
					lcdcmd(0xcc);
}
ISR(INT1_vect)
{
	//PORTA=~PORTA;
	pulse++;
//	_delay_ms(100);
}
int main(void)
{
	DDRB=0xff;
	DDRD=0x07;
	PORTD|=(1<<PD3);
	lcd_init();
	lcdstr("OUTPUT:-");
	//init_ports();
    while(1)
    {
		init_interrupts();
		display();
	}
    
}

void lcd_init()	 		// function for LCD initialization
{
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x82);
}

void lcdcmd(unsigned char cmdout)
{
	lcd=cmdout;
	PORTD=(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(5);
	PORTD=(0<<rs)|(0<<rw)|(0<<en);
	
}


void lcddata(unsigned char dataout)
{
	lcd=dataout;
	PORTD=(1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(5);
	PORTD=(1<<rs)|(0<<rw)|(0<<en);
}

void lcdstr(unsigned char *s)
{
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		lcddata(*s);
		s++;
	}
}