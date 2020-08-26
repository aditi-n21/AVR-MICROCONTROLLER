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
void character(void);

int main(void)
{
	unsigned char i;
	DDRB=0xff;
	DDRA=0xff;
	lcdinit();
	while(1)
	{
	character();
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

void character(void)
{
writecmd(64);  //Address where values of the first custom character is stored
writedata(0);
writedata(10);
writedata(21);
writedata(17);
writedata(10);
writedata(4);
writedata(0);
writedata(0);
writecmd(0xC0);  //Address of the location where the character is to be displayed
writedata(0);  // Displaying the character created at address 0x64 
_delay_ms(50);

writecmd(72);
writedata(0);
writedata(0);
writedata(0);
writedata(10);
writedata(0);
writedata(4);
writedata(17);
writedata(14);
writecmd(0x80);
writedata(1);
_delay_ms(50);

writecmd(80);
writedata(0);
writedata(0);
writedata(10);
writedata(0);
writedata(4);
writedata(0);
writedata(14);
writedata(17);
writecmd(0x82);
writedata(2);
_delay_ms(50);
writecmd(88);
writedata(1);
writedata(3);
writedata(5);
writedata(9);
writedata(9);
writedata(11);
writedata(27);
writedata(24);
writecmd(0x84);
writedata(3);
_delay_ms(50);

writecmd(96);
writedata(0);
writedata(10);
writedata(0);
writedata(31);
writedata(17);
writedata(14);
writedata(0);
writedata(0);
writecmd(0x86);
writedata(4);
_delay_ms(50);

writecmd(104);
writedata(10);
writedata(0);
writedata(4);
writedata(0);
writedata(14);
writedata(17);
writedata(17);
writedata(14);
writecmd(0xC2);
writedata(5);
_delay_ms(50);

writecmd(112);
writedata(0);
writedata(10);
writedata(0);
writedata(0);
writedata(4);
writedata(0);
writedata(31);
writedata(0);
writecmd(0xC4);
writedata(6);
_delay_ms(50);

writecmd(120);
writedata(0);
writedata(17);
writedata(10);
writedata(17);
writedata(4);
writedata(0);
writedata(14);
writedata(17);
writecmd(0xC6);
writedata(7);
_delay_ms(50);
}