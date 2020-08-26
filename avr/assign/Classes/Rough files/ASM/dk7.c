#include<reg51.h>
#include<string.h>
#define lcd P0
sbit rs=P3^6 ;
//sbit rw=P3^5;
sbit en=P3^7;
void character(void);
void lcd_str(unsigned char *);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay(unsigned char);
void lcd_init(void);
void main()
{ 
lcd_init();
while(1)
{
character();
}
}
void lcd_cmd(unsigned char a)
{  
lcd=a;
rs=0;
//rw=0;
en=1;
delay(1);
en=0;
}
void lcd_data(unsigned char b)
{
lcd=b;
rs=1;
//rw=0;
en=1;
delay(1);
en=0;
}
void delay(unsigned char msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)
for(j=0;j<1275;j++);
}
void lcd_init(void)
{
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x0e);
lcd_cmd(0x80);
}
void character(void)
{
lcd_cmd(64);
lcd_data(2);
lcd_data(6);
lcd_data(14);
lcd_data(11);
lcd_data(11);
lcd_data(24);
lcd_data(24);
lcd_cmd(0x85);
lcd_data(0);
delay(2);
}

void lcd_str(unsigned char *s)
{
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
	lcd_data(*s);
	s++;
	}
}			   
