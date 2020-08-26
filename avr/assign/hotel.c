/*
 * hotel.c
 *
 * Created: 9/2/2015 6:22:02 PM
 *  Author: DELL_PC
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define data PORTD
#define control PORTD
#define rs PD0
#define rw PD1
#define en PD2

void lcd_init(void)
{
	cmndbrk(0x02);
	cmndbrk(0x28);
	cmndbrk(0x01);
	cmndbrk(0x06);
	cmndbrk(0x0e);
	cmndbrk(0x80);
}

void cmnd(unsigned char c)
{
	data=c;
	control&=~(1<<rs);
	control&=~(1<<rw);
	control|=(1<<en);
	_delay_ms(50);
	control&=~(1<<en);
	
}

void dat(unsigned char d)
{
	data=d;
	control|=(1<<rs);
	control&=~(1<<rw);
	control|=(1<<en);
	_delay_ms(50);
	control&=~(1<<en);
}


void cmndbrk(unsigned char r)
{
	unsigned char k;
	k=r&0xf0;
	cmnd(k);
	r=r<<4;
	k=r&0xf0;
	cmnd(k);
}

void datbrk(unsigned char o)
{
	unsigned char h;
	h=o&0xf0;
	dat(h);
	o=o<<4;
	h=o&0xf0;
	dat(h);
}

void str(unsigned char *s)
{
	while(*s)
	{
		datbrk(*s);
		s++;
		_delay_ms(50);
	}
	
}


int main(void)
{
	DDRC=DDRD=0xff;
	lcd_init();
	while(1)
	{
		cmndbrk(0x80);
		str("WELCOME TO HOTEL");
		cmndbrk(0xc2);
		str("TRANSYLVANIA");
		_delay_ms(500);
		cmndbrk(0x01);
		cmndbrk(0x80);
		str("CHICKEN");
		cmndbrk(0x8a);
		str("MUTTON");
		cmndbrk(0xc0);
		str("NAAN");
		cmndbrk(0xcb);
		str("SABJI");
		_delay_ms(500);
		cmndbrk(0x01);
		cmndbrk(0x80);
		str("PARANTHA");
		cmndbrk(0x8c);
		str("DAAL");
		cmndbrk(0xc0);
		str("DESERT");
		cmndbrk(0xcb);
		str("PAPAD");
		_delay_ms(500);
		cmndbrk(0x01);
		cmndbrk(0x83);
		str("ENTER YOUR");
		cmndbrk(0xc5);
		str("CHOICE");
		_delay_ms(100);
		cmndbrk(0x01);
		
	}
}