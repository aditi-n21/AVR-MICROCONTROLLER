/*
 * _4x3_1_9_a0c.c
 *
 * Created: 9/4/2015 7:37:59 PM
 *  Author: vipul
 */ 



#include <avr/io.h>
#define col1 PB0
#define col2 PB1
#define col3 PB2
#define rw1 PB3
#define rw2 PB4
#define rw3 PB5
#define rw4 PB6
#define key_in PINB
#define key PORTB
#define seg PORTC
void keysence(void)
{
	key&=~(1<<col1);
	key|=(1<<col2)|(1<<col3);
	if(bit_is_clear(key_in,rw1))
	{
		seg=0x06;
	}
	if(bit_is_clear(key_in,rw2))
	{
		seg=0x66;
	}
	if(bit_is_clear(key_in,rw3))
	{
		seg=0x07;
	}
	if(bit_is_clear(key_in,rw4))
	{
		seg=0x77;
	}
	
	key&=~(1<<col2);
	key|=(1<<col1)|(1<<col3);
	if(bit_is_clear(key_in,rw1))
	{
		seg=0x5b;
	}
	if(bit_is_clear(key_in,rw2))
	{
		seg=0x6d;
	}
	if(bit_is_clear(key_in,rw3))
	{
		seg=0x7f;
	}
	if(bit_is_clear(key_in,rw4))
	{
		seg=0x3f;
	}
	
	key&=~(1<<col3);
	key|=(1<<col2)|(1<<col1);
	if(bit_is_clear(key_in,rw1))
	{
		seg=0x4f;
	}
	if(bit_is_clear(key_in,rw2))
	{
		seg=0x7d;
	}
	if(bit_is_clear(key_in,rw3))
	{
		seg=0x6f;
	}
	
	if(bit_is_clear(key_in,rw4))
	{
		seg=0x39;
	}
}
int main(void)
{
	
	
	DDRC=0xff;
	DDRB&=~((1<<rw1)|(1<<rw2)|(1<<rw3)|(1<<rw4));
	DDRB|=(1<<col1)|(1<<col2)|(1<<col3);
	PORTB|=(1<<rw1)|(1<<rw2)|(1<<rw3)|(1<<rw4);
	while(1)
	{
		keysence();
	}
}