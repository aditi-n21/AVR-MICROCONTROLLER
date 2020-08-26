#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
#define lcd PORTB
#define ctrl PORTA
#define rs 0
#define rw 1
#define en 2

void writecmd(unsigned char);
void writedata(unsigned char);
void writestr(unsigned char *);
void lcdinit(void);

int main(void)
{
	unsigned char i;
	DDRB=0xff;
	DDRA=0xff;
	lcdinit();
	writecmd(0x80);
	//	writecmd(0xc5);
	writestr("WELCOME TO CETPA");
	//writedata('A');
	while(1)
	{
	for(i=0;i<16;i++)
	{
	writecmd(0x1c);
	_delay_ms(200);
	}	
	for(i=0;i<16;i++)
	{
	writecmd(0x18);
	//writestr(" ");
	_delay_ms(200);
	}
	}
}
void lcdinit(void)
{
	writecmd(0x38);
	writecmd(0x0c);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
	
}

void writecmd(unsigned char a)
{
	lcd=a;
	ctrl&=~(1<<rs);
	ctrl&=~(1<<rw);
	ctrl|=(1<<en);
	_delay_ms(5);
	ctrl&=~(1<<en);
	
}

void writedata(unsigned char b)
{	lcd=b;
	ctrl|=(1<<rs);
	ctrl&=~(1<<rw);
	ctrl|=(1<<en);
	_delay_ms(5);
	ctrl&=~(1<<en);
}
void writestr(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		writedata(*s);
		s++;
	}
}

