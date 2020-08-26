/*
 * lcd_4.c
 *
 * Created: 01-08-2012 PM 3:03:04
 *  Author: MANOJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>

#define LCD PORTB
#define en PB0
#define rw PB1
#define rs PB2

void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);

int main(void)
{
    unsigned char data0[]="WELCOME";
	unsigned char data1[]="HOME(ECE)";
	unsigned int i=0;
	DDRB=0xff;
	lcd_init();
	
	while(data0[i]!='\0')
	{
		lcd_data1(data0[i]);
		_delay_ms(200);
		i++;
	}
	lcd_cmd1(0xc7);
	i=0;
	while(data1[i]!='\0')
	{
		lcd_data1(data1[i]);
		_delay_ms(200);
		i++;
	}	
	//lcd_data1('A');
	while(1);	
		
    return 0; 
}

void lcd_init(void)
{
	lcd_cmd1(0x02);
	_delay_ms(1);
	lcd_cmd1(0x28);
	_delay_ms(1);
	lcd_cmd1(0x01);
	_delay_ms(1);
	lcd_cmd1(0x0e);
	_delay_ms(1);
	lcd_cmd1(0x0c);
	_delay_ms(1);
	lcd_cmd1(0x82);
	_delay_ms(1);
}	
void lcd_cmd(unsigned char value)
{
	LCD=value;
	LCD&=~(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(1);
	LCD&=~(1<<en);
	_delay_ms(50);
}
void lcd_cmd1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_cmd(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_cmd(cd1);
}	

void lcd_data(unsigned char value)
{
	LCD=value;
	LCD|=(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(1);
	LCD&=~(1<<en);
	_delay_ms(50);

}
void lcd_data1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_data(cd1);
}	

