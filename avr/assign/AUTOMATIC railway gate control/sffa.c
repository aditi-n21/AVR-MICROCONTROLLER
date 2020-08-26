//Program to display numeric digit 0-9 on LCD
#include<reg51.h>
#include<string.h>
#define LCD P1
sbit RS = P3^7;   //Register select (RS) pin
sbit RW = P3^6;   //Read write (RW) pin
sbit EN = P3^5;   //Enable (EN) pin
sbit sense1= P3^0;
sbit sense2= P3^1;
sbit mot1a=P2^0;
sbit mot1b=P2^1;
sbit mot2a=P2^2;
sbit mot2b=P2^3;
void delay(unsigned int);
void writecmd(unsigned char);
void writedata(unsigned char);
void writestr(unsigned char *);
void lcd(void);

void delay(unsigned int delay_time)    // Time delay function
{
unsigned int j,k;
for(j=0;j<=delay_time;j++)
  for(k=0;k<=1275;k++);		 
}
void writecmd(unsigned char a)
{
	RS=0;
	LCD=a;
	RW=0;
	EN=1;
	delay(5);
	EN=0;
	return;
}
void writedata(unsigned char b)
{
	RS=1;
	LCD=b;
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

void lcd(void)
{
	writecmd(0x38);
	writecmd(0x0c);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x85);
}
	

void main()
{ 
	unsigned char cnt;
	sense1=sense2=1;
	lcd();
writecmd(0x82);
writestr("WELCOME TO");
writecmd(0xc0);
writestr("AUTOMATIC RAILWAY");
writecmd(0x01);
writecmd(0x82);
writestr("GATE CONTROL");
writecmd(0xc5);
writestr("PROJECT");

 
	while(1)
{
	
mot1a=0;mot1b=0;mot2a=0;mot2b=0;
	writecmd(0x82);
writestr("SCANNING>>>>>>");

	if((sense1==1)||(sense2==1))
	{
		if(cnt==1)
		{
		writecmd(0x01);
writecmd(0x82);
writestr(" CLOSING GATE ");
  mot1a=1;mot1b=0;mot2a=1;mot2b=0;
delay(500);
			cnt=0;
		}			
}
else 
{
	if(cnt==0)
	{
writecmd(0x01);
writecmd(0x82);
writestr("OPENING GATE");
mot1a=0;mot1b=1;mot2a=0;mot2b=1;
delay(500);
cnt=1;
	}
		
}
}
}