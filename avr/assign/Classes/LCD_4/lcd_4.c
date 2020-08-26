#include <reg51.h>
#include <string.h>

#define LCD P1
sbit en = P1^2;
sbit rw = P1^1;
sbit rs = P1^0;

void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void delay(unsigned char);
void main(void)
{
    lcd_init();
	lcd_str("WELCOME");
	lcd_cmd1(0xc7);
	lcd_str("HOME");
	while(1);	
}
void lcd_str(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		lcd_data1(*s);
		s++;
	}
}

void lcd_init(void)
{
	lcd_cmd1(0x02);
	delay(5);
	lcd_cmd1(0x28);
	delay(5);
	lcd_cmd1(0x01);
	delay(5);
	lcd_cmd1(0x0e);
	delay(5);
	lcd_cmd1(0x06);
	delay(5);
	lcd_cmd1(0x82);
	delay(5);
}	
void lcd_cmd(unsigned char value)
{
	LCD=value;
	rs=0;
	rw=0;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_cmd1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_cmd(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_cmd(cd1);
}	
void delay(unsigned char itime)
{
unsigned char i;
unsigned int j;
for(i=0;i<itime;i++)
for(j=0;j<1275;j++);

}
void lcd_data(unsigned char value)
{
	LCD=value;
	rs=1;
	rw=0;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_data(cd1);
}	

