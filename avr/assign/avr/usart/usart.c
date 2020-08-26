/*
 * usart.c
 *
 * Created: 8/17/2015 5:10:56 PM
 *  Author: what
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define LCD PORTC
#define en PC2
#define rw PC1
#define rs PC0
#define sw PB0

void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
unsigned char usart_recieve(void);
void usart_transmit(unsigned char send);
void usart_init();
void usart_transmit_str(unsigned char *s);

int main(void)
{
	DDRD=0xfe;
	DDRC=0xff;
	DDRB&=~(1<<sw);
	PORTB|=(1<<sw);
	
	unsigned char k;

	lcd_init();
	usart_init();
	lcd_cmd1(0x80);
	lcd_str("Welcome");
	usart_transmit_str("Welcome\r\n");
    while(1)
  {
if (bit_is_clear(PINB,sw))
{
	 usart_transmit_str("\nAT\r\n");
	 _delay_ms(2000);
	 _delay_ms(1000);
	   usart_transmit_str("\nAT+CMGF=1\r\n");
	 _delay_ms(2000);
	 _delay_ms(1000);  
	 	   usart_transmit_str("\nAT+CMGS=\"+919720446950\"\r\n");
	 	   _delay_ms(2000);
	 	   _delay_ms(1000);
				   usart_transmit_str("Hello Brother");
				   _delay_ms(2000);
				   _delay_ms(1000);
		usart_transmit(0x1a);   	
		 _delay_ms(2000);
		 _delay_ms(3000);	
		 _delay_ms(1000);  
		 lcd_cmd1(0xc0);
		 lcd_str("MSG SENT"); 
}
    }
}

void usart_init()
{
	UCSRB|= (1 << TXEN) | (1 << RXEN);
	UCSRC|= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
	UBRRL=51;
}

void usart_transmit(unsigned char send)
{
	while(!(UCSRA & (1 << UDRE)));
	UDR = send; 
}
unsigned char usart_recieve(void)
{
	while ((UCSRA & (1 << RXC)) == 0);	
	return(UDR); 
}
void usart_transmit_str(unsigned char *s)
{
	while(*s)
	{
		usart_transmit(*s);
		s++;
		_delay_ms(100);
	}
}
void lcd_init(void)
{
	lcd_cmd1(0x02);
	_delay_ms(10);
	lcd_cmd1(0x28);
	_delay_ms(10);
	lcd_cmd1(0x01);
	_delay_ms(10);
	lcd_cmd1(0x06);
	_delay_ms(10);
	lcd_cmd1(0x0e);
	_delay_ms(10);
	lcd_cmd1(0x80);
	_delay_ms(10);
}
void lcd_cmd(unsigned char value)
{
	LCD=value;
	LCD&=~(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(10);
	LCD&=~(1<<en);
	_delay_ms(10);
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
	_delay_ms(10);

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
	   _delay_ms(100);
   }	
}