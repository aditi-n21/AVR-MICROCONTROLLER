#include<avr/io.h>
#include<util/delay.h>
void uart_int();
void uart_send(unsigned char ch);
int main()
{	
	uart_ini();
	while(1)
	{

	uart_send(0x0d);		//carriage return
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
	UCSRB|=(1<<TXEN);
	UCSRC|=(1<<URSEL)|(1<<UCSZ0)|(1<<UCSZ1);	//Tx using 8-bit format
	UBRRL=0x33;			//Baud rate =9600
}

void uart_send(unsigned char ch)
{	UDR=ch;
	while(!(UCSRA & (1<<TXC)));
				//data is Txed using UDR reg. like SBUF in 8051			
}