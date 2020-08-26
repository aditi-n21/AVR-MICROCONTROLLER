

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>

#define data PORTB
#define rs PB0
#define rw PB1
#define en PB2

void lcd_init(void);
void cmd (unsigned char cd);
void command(unsigned char c);
void display(unsigned char d);
void dis (unsigned char ds);
void print(unsigned char *str);



void ADC_init(void)		// Initialization of ADC
{
	ADMUX=(1<<REFS0);	// AVcc with external capacitor at AREF
	ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	// Enable ADC and set Pre-scaler division factor as 128
}

unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111;		// channel must be b/w 0 to 7
	ADMUX |= ch;				// selecting channel
	ADCSRA|=(1<<ADSC);			// start conversion
	while(!(ADCSRA & (1<<ADIF)));	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);			// clearing of ADIF, it is done by writing 1 to it
	return (ADC);
}


void usart_init()
{
	UCSRB |= (1 << TXEN) | (1 << RXEN);
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL=51;
	
}

void usart_putch(unsigned char send)
{
	
	while(!(UCSRA & (1 << UDRE)));
	UDR = send;
}
void send_str(unsigned char *str)
{
	while (*str!='\0')
	{
		usart_putch(*str++);
	}
}
unsigned int usart_getch()
{
	while ((UCSRA & (1 << RXC)) == 0);				// Do nothing until data have been received and is ready to be read from UDR
	return(UDR); // return the byte

	//PORTC=UDR;
}

int main(void)
{
	DDRB=0xff; // lcd
	unsigned int value;
	ADC_init();
	usart_init();
	lcd_init();
	print("welcome to gsm");
	cmd(0xc0);
	print("based system");
	
	_delay_ms(500);
	cmd(0x01);
	cmd(0x80);
	
	while(1)
	{
		value=ADC_read(0);
		if (value>=728)
		{
			print("accident occur!!");
			send_str("AT\r");
			
			_delay_ms(1000);
			_delay_ms(1000);
			send_str("AT\r");
			//send_str("13");
			_delay_ms(1000);
			_delay_ms(1000);
			send_str("AT+CMGF=1\r");
			_delay_ms(1000);
			_delay_ms(1000);
			send_str("AT+CMGS=7838621969;\r");
			_delay_ms(1000);
			_delay_ms(1000);
			send_str("ACCIDENT OCCURED\r");
			_delay_ms(200);
			usart_putch(0x1a);
			_delay_ms(1000);
		}
	}
}


void lcd_init(void)
{
	cmd(0x02);
	cmd(0x28);
	cmd(0x01);
	cmd(0x06);
	cmd(0x0e);
	cmd(0x80);
}
void cmd(unsigned char cd)
{
	unsigned char y;
	y=cd & 0xf0;
	command(y);
	y=cd<<4 & 0xf0;
	command(y);
}
void command(unsigned char c)
{
	data=c;
	data &=~(1<<rs);
	data|=(1<<en);
	_delay_ms(50);
	data&=~(1<<en);
}

void dis(unsigned char ds)
{
	unsigned char x;
	x=ds & 0xf0;
	display(x);
	x=ds<<4 & 0xf0;
	display(x);
}

void display(unsigned char d)
{
	data=d;
	data|=(1<<rs);
	data|=(1<<en);
	_delay_ms(50);
	data&=~(1<<en);
}

void print(unsigned char *str)
{
	while (!(*str=='\0'))
	{
		dis(*str++);
	}
}
