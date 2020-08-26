/*
 * lcd_comm_with_strg.c
 *
 * Created: 9/22/2015 11:05:24 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include <util/delay.h>
void usart_int (void)
{
	UCSRB=(1<<TXEN)|(1<<RXEN);
	UCSRC=(1<<UCSZ1)|(1<<UCSZ0)|(1<<URSEL);
	UBRRL=0X33;
}
void usart_send (unsigned char ch)
{
	while (!((UCSRA)&(1<<UDRE)));
	UDR=ch;
}
unsigned char usart_get (void)
{	
	while (!((UCSRA)&(1<<RXC)));
		return UDR;
}}	
int main(void)
{
	DDRD=0xfe;
	unsigned char k;
	usart_int();
	while(1)
	{
		k= usart_get();
		usart_send(k);
	
	}
}