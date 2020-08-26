#include<reg51.h>
#include<string.h>
#define lcd P0
sbit rs=P3^0 ;
sbit rw=P3^1;
sbit en=P3^2;
void character(void);
void lcd_str(unsigned char *);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void delay(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);

void main()
{
unsigned int i; 
lcd_init();
while(1)
{ lcd_cmd1(0x80);
  lcd_str("WELCOME");
  for(i=0;i<16;i++)
     { lcd_cmd1(0x18);
	   delay(100);
	 }
  for(i=0;i<16;i++)
      {
	  lcd_cmd1(0x1C);
	  delay(100);
	  }
}
}
void lcd_cmd1(unsigned char value)
{
unsigned char cd1;
cd1=value & 0xf0;
lcd_cmd(cd1);
cd1=(value<<4) & 0xf0;
lcd_cmd(cd1);
}

void lcd_cmd(unsigned char a)
{  
lcd=a;
rs=0;
rw=0;
en=1;
delay(1);
en=0;
}
void lcd_data1(unsigned char value)
{
unsigned char cd1;
cd1=value & 0xf0;
lcd_data(cd1);
cd1=(value<<4) & 0xf0;
lcd_data(cd1);
}

void lcd_data(unsigned char b)
{
lcd=b;
rs=1;
rw=0;
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
lcd_cmd1(0x02);
lcd_cmd1(0x28);
lcd_cmd1(0x01);
lcd_cmd1(0x06);
lcd_cmd1(0x0e);
lcd_cmd1(0x80);
}
void character(void)
{
lcd_cmd1(64);
lcd_data1(2);
lcd_data1(6);
lcd_data1(14);
lcd_data1(11);
lcd_data1(11);
lcd_data1(24);
lcd_data1(24);
lcd_cmd1(0x85);
lcd_data1(0);
delay(2);
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
