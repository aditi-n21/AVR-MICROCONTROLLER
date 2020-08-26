/*
 * lcd_8.c
 *
 * Created: 30-07-2012 PM 9:25:27
 *  Author: MANOJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define LCD PORTC
#define ctrl PORTD
#define en PD2
#define rw PD1
#define rs PD0

void lcd_cmd(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);

int main(void)
{
    DDRC=0xff;
	DDRD=0xff;
	lcd_init();
	//lcd_cmd(0x85);
	//lcd_data('O');
	//lcd_data('K');
	_delay_ms(100);
	//lcd_cmd(0x01);
	while(1)
    {
		lcd_cmd(0x80);
		lcd_str("WELCOME TO THE");
		lcd_cmd(0xC2);
		lcd_str(" ATMEGA WORLD");
     _delay_ms(500);
	}
	return 0; 
}

void lcd_init(void)
{
	lcd_cmd(0x38);
	_delay_ms(10);
	lcd_cmd(0x01);
	_delay_ms(10);
	lcd_cmd(0x0e);
	_delay_ms(10);
	lcd_cmd(0x06);
	_delay_ms(10);
	lcd_cmd(0x80);
	_delay_ms(10);
}	
void lcd_cmd(unsigned char value)
{
	LCD=value;
	ctrl&=~(1<<rs);
	ctrl|=(1<<en);
	ctrl&=~(1<<rw);
	_delay_ms(10);
	ctrl&=~(1<<en);
	_delay_ms(50);
}
void lcd_data(unsigned char value)
{
	LCD=value;
	ctrl|=((1<<rs)|(1<<en));
	ctrl&=~(1<<rw);
	_delay_ms(10);
	ctrl&=~(1<<en);
	_delay_ms(50);
}
void lcd_str(unsigned char *s)
{
	unsigned char i,l;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		lcd_data(*s);
		s++;
		_delay_ms(100);
	}
}