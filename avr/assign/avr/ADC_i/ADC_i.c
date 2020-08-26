/*
 * ADC_i.c
 *
 * Created: 16-08-2012 PM 4:25:04
 *  Author: MANOJ
 */ 

//Program to use internal ADC of AVR microcontroller using interrupts
#include<avr/io.h>
#include<util/delay.h>
#include<avr/interrupt.h>
#include <string.h>
 
#define lcd PORTC
#define rs PD0
#define rw PD1
#define en PD2
 
void adc_init(void);
unsigned int adc_read(void);
void adc_conversion(uint16_t);
void lcd_init(void);
void lcdcmd(unsigned char);
void lcddata(unsigned char);
void lcdstr(unsigned char*);
 
uint16_t adc_out;
//unsigned char position;
int main()
{
	int i=0;
	DDRD=0x07;
	//DDRB=0xFF;
	DDRC=0xFF;
	lcd_init();
	lcdcmd(0x82);
	lcdstr("ADC TEST-");
	//lcdcmd(0x01);
 	adc_init();
 	/* Configure timer0*/
 	TCCR0=(5<<CS00);	
	TIMSK=(1<<TOIE0);
 	sei();
	while(1);
	/*{
		lcdcmd(0x80);
		lcdstr("ADC0=");
		SFIOR|=(1<<ACME);
		ADMUX=0X00;
		position=0x89;
		_delay_ms(50);
		lcdcmd(0xc0);
		lcdstr("ADC1=");
		SFIOR|=(1<<ACME);
		ADMUX=0X01;
		position=0xc9;
		_delay_ms(50);
		
	}*/
}
 
void adc_init()			// ADC configuration
{
	ADMUX=(1<<REFS0);	//Vref=AVcc
	// ADSC=1 ADC Enable
	// ADPS[2:0]=111, prescaler=128
	// ADIE=1, ADC interrupt Enable
	//ADATE=1, ADC Auto Triggering Enable
	//ADTS[2:0]= 100 , Timer0 overflow select as trigger source
	ADCSRA=(1<<ADEN)|(7<<ADPS0)|(1<<ADSC)|(1<<ADIE)|(1<<ADATE);
	SFIOR=(4<<ADTS0);
}
 
ISR(ADC_vect)
{
	adc_conversion((ADC));
}
ISR(TIMER0_OVF_vect)
{
	
}
 
/* this function is written to convert interger value to their corresponding ASCII value*/
void adc_conversion(uint16_t adc_out)  
{
	unsigned int adc_out1;
	int i=0;
	unsigned char position=0xC3;
	for(i=0;i<=3;i++)
	{
		adc_out1=adc_out%10;
		adc_out=adc_out/10;
		lcdcmd(position);
		lcddata(48+adc_out1);
		position--;
	}
}
 
void lcd_init()	 		// fuction for LCD initialization
{
	lcdcmd(0x38);
	lcdcmd(0x0C);
	lcdcmd(0x01);
	lcdcmd(0x06);
	lcdcmd(0x80);
}
 
void lcdcmd(unsigned char cmdout)	
{
	lcd=cmdout;
	PORTD=(0<<rs)|(0<<rw)|(1<<en);
	_delay_ms(10);
	PORTD=(0<<rs)|(0<<rw)|(0<<en);
		
}
 
 
void lcddata(unsigned char dataout)
{
	lcd=dataout;
	PORTD=(1<<rs)|(0<<rw)|(1<<en);
	_delay_ms(10);
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