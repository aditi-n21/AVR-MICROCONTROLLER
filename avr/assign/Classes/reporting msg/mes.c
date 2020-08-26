//Program to display numeric digit 0-9 on LCD

#include<reg51.h>
#include<string.h>
sbit RS = P3^6;   //Register select (RS) pin
//sbit RW = P3^6;   //Read write (RW) pin
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
	P0=a;
	//RW=0;
	EN=1;
	delay(5);
	EN=0;
	return;
}

void writedata(unsigned char b)
{
	RS=1;
	P0=b;
//	RW=0;
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
while(1)
{
lcd();
writecmd(0x80);
writestr("WELCOME TO");
writecmd(0xc8);
writestr("CETPA");
delay(10);
writecmd(0x01);
writecmd(0x80);
writestr("EMBEDDED SYSTEM");
writecmd(0xc4);
writestr("8051 PIC AVR");
delay(10);
writecmd(0x01);
writecmd(0x83);
writestr("MATLAB");
writecmd(0xc7);
writestr("VHDL");
delay(10);
writecmd(0x01);
writecmd(0x83);
writestr("PLC");
writecmd(0xc7);
writestr("SCADA");
delay(10);
writecmd(0x01);
writecmd(0x83);
writestr("AUTOCAD");
writecmd(0xc7);
writestr("CATIA");
delay(10);
writecmd(0x01);
writecmd(0x83);
writestr("JAVA");
writecmd(0xc7);
writestr(".NET");
delay(10);
}
}