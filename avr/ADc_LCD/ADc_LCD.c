/*
 * ADc_LCD.c
 *
 * Created: 03-01-2014 PM 6:53:39
 *  Author: MANOJ
 */ 

#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
 
#define LCD PORTD
#define en PD2
#define rw PD1
#define rs PD0

void ADC_init(void);
unsigned int ADC_read(unsigned char);
void adc_conversion(uint16_t,unsigned char);
void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void character(void);

int main(void)
{
   	unsigned int value;
	   unsigned char i;
	DDRD=0xFF;
	lcd_init();
	ADC_init();	
	lcd_str("TEMP IS...");
lcd_cmd1(0xca);
lcd_str(" 'C");
	
	while(1)
	{
	value=ADC_read(5);
	value=value/2;
		adc_conversion(value,0xc9);		
	}
}		
void ADC_init(void)		// Initialization of ADC
{
	ADMUX|=(1<<REFS0)|(1<<REFS1);	// AVcc with external capacitor at AREF
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	
						// Enable ADC and set Prescaler division factor as 128
}
 
unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111;		// channel must be b/w 0 to 7
	ADMUX |= ch;				// selecting channel
 
	ADCSRA|=(1<<ADSC);			// start conversion
	while((ADCSRA & (1<<ADIF))==0);	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);			// clearing of ADIF, it is done by writing 1 to it
   	   return (ADC);
}

void adc_conversion(unsigned int adc_out,unsigned char position)  
{
	unsigned int adc_out1;
	int i=0;
	for(i=0;i<=1;i++)
	{
		adc_out1=adc_out%10;
		adc_out=adc_out/10;
		lcd_cmd1(position);
		lcd_data1(48+adc_out1);
		position--;
	}
}

void lcd_init(void)
{
	lcd_cmd1(0x02);
	lcd_cmd1(0x28);
	lcd_cmd1(0x01);
	lcd_cmd1(0x06);
	lcd_cmd1(0x0e);
	lcd_cmd1(0x80);
	}
void lcd_cmd(unsigned char value)
{
	LCD=value;
	LCD&=~(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(10);
	LCD&=~(1<<en);
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
	_delay_ms(10);
	LCD&=~(1<<en);

}
void lcd_data1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data(cd1);
		cd1=(value<<4) & 0xf0;
	lcd_data(cd1);
}

void lcd_str(unsigned char *s)
{
	while(*s)
	{
		lcd_data1(*s);
		s++;
		_delay_ms(10);
	}
}
