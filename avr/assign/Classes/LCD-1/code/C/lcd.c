//Program to display numeric digit 0-9 on LCD

#include<reg51.h>
#include<string.h>
sbit RS = P3^5;   //Register select (RS) pin
sbit RW = P3^6;   //Read write (RW) pin
sbit EN = P3^7;   //Enable (EN) pin


void delay(int delay_time)    // Time delay function
{
int j,k;
for(j=0;j<=delay_time;j++)
  for(k=0;k<=1000;k++);
}

void writecmd(unsigned char a)
{
	RS=0;
	P1=a;
	RW=0;
	EN=1;
	delay(5);
	EN=0;
	return;
}

void writedata(unsigned char b)
{
	RS=1;
	P1=b;
RW=0;
	EN=1;
	delay(5);
	EN=0;
	return;
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
/*void writestrslow(unsigned char *s)
{	
    unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		writedata(*s);
		s++;
		msdelay(150);
	}
}  */
void lcd()
{
	writecmd(0x38);
	writecmd(0x0c);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
	
}
void main()
{
	unsigned char i;
lcd();
writecmd(0x8d);
//	writecmd(0xc5);
writestr("PANTNAGAR....");
while(1)
{
	for(i=0;i<28;i++)
{writecmd(0x1c);
delay(25);
}	for(i=0;i<28;i++)
{writecmd(0x18);
//writestr(" ");
delay(25);
}
}


}