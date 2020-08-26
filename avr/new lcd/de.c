#include<reg51.h>
#define lcd P2
sbit rs=P3^0;
sbit rw=P3^1;
sbit en=P3^2;
void lcd_dat(unsigned char d);
void lcd_cmd(unsigned char g);
void strn(unsigned char *);
void initial();
void delay(unsigned char tm);
void dat(unsigned char y);
void cmd(unsigned char x);
void initial()
{
lcd_cmd(0x01);
	lcd_cmd(0x02);
	lcd_cmd(0x0e);
	lcd_cmd(0x06);
	lcd_cmd(0x28);
	lcd_cmd(0x80);
}
void lcd_cmd(unsigned char g)
{
	int m;
	m=g&0xf0;
cmd(m);
	m=((g<<4)&0xf0);
	cmd(m);
}
void strn(unsigned char *s)
{
	while(*s)
	{
		lcd_dat(*s);
		s++;
	}
}
void lcd_dat(unsigned char d)
{
	int z;
	z=d&0xf0;
	dat(z);
	z=(d<<4)&0xf0;
	dat(z);
}
void cmd(unsigned char x)
{
	lcd=x;
	rs=0;
	rw=0;
	en=1;
	delay(5);
	en=0;
}

void dat(unsigned char y)
{
	lcd=y;
	rs=1;
	rw=0;
	en=1;
	delay(5);
	en=0;
}

void delay(unsigned char tm)
{
	int i,j;
	for(i=0;i<tm;i++)
	{
		for(j=0;j<30000;j++);
	}
}
void main()
{
	lcd =0x00;
	initial();
	while(1)
	{
		strn("my name is sakshi");
	}
}
