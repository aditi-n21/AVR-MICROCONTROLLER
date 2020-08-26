#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#define lcd PORTB

#define rs 0
#define rw 1
#define en 2

void writecmd(unsigned char);
void writedata(unsigned char);
void writestr(unsigned char *);
void lcdinit(void);
void writecmd1(unsigned char);
void writedata1(unsigned char);

int main(void)
{
	unsigned char i;
	DDRB=0xff;
	lcdinit();
	writecmd1(0x80);
	//	writecmd(0xc5);
	writestr("WELCOME TO CETPA");
	//writedata('A');
	while(1)
	{
	for(i=0;i<16;i++)
	{
	writecmd1(0x1c);
	_delay_ms(200);
	}	
	for(i=0;i<16;i++)
	{
	writecmd1(0x18);
	//writestr(" ");
	_delay_ms(200);
	}
	}
}
void lcdinit(void)
{
writecmd1(0x02);
	writecmd1(0x28);
	writecmd1(0x0c);
	writecmd1(0x01);
	writecmd1(0x06);
	writecmd1(0x80);
	
}

void writecmd(unsigned char a)
{
	lcd=a;
	lcd&=~(1<<rs);
	lcd&=~(1<<rw);
	lcd|=(1<<en);
	_delay_ms(5);
	lcd&=~(1<<en);
	
}

void writedata(unsigned char b)
{	lcd=b;
	lcd|=(1<<rs);
	lcd&=~(1<<rw);
	lcd|=(1<<en);
	_delay_ms(5);
	lcd&=~(1<<en);

}
void writestr(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		writedata1(*s);
		s++;
	}
}
void writecmd1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	writecmd(cd1);
	cd1=(value<<4) & 0xf0;
	writecmd(cd1);
}	
void writedata1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	writedata(cd1);
	cd1=(value<<4) & 0xf0;
	writedata(cd1);
}	
