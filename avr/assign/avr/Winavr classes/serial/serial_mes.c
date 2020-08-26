#include<avr/io.h>// baud rate = 9600 and freq. = 8MHz
#include<util/delay.h>
void uart_int();
void uart_send(unsigned char ch);
int main()
{	unsigned char ar[]="********Welcome to HYPER TERMINAL*********" ;
	unsigned char ar1[]="    *Through Atmega32 using RS232 Port*" ;
	unsigned char ar2[]="      Programme executed successfully";
	unsigned char ar3[]="        Conratulation to Pragrammer";
	unsigned char *p,*p1,*p2,*p3;
	p=ar;p1=ar1;p2=ar2;p3=ar3;
	uart_ini();
	while(1)
	{

	while(*p)
	{
		uart_send(*p++);
		_delay_ms(100);
	}
	uart_send(0x0d);	//carriage return
	_delay_ms(100);
	while(*p1)
	{
		uart_send(*p1++);
		_delay_ms(100);
	}
	uart_send(0x0d);
	_delay_ms(100);
	while(*p2)
	{
		uart_send(*p2++);
		_delay_ms(100);
	}
	uart_send(0x0d);
	_delay_ms(100);
	while(*p3)
	{
		uart_send(*p3++);
		_delay_ms(100);
	}
	uart_send(0x0d);
	_delay_ms(100);
	uart_send('B');
	_delay_ms(100);
	uart_send('Y');
	_delay_ms(100);
	uart_send('E');
	_delay_ms(100);
	}

	
}
void uart_ini()
{
	UCSRB|=(1<<RXEN)|(1<<TXEN);
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);
	UBRRL=0x33;
}

void uart_send(unsigned char ch)
{
	while(!(UCSRA & (1<<UDRE)));
	UDR=ch;
}