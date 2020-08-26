#include<reg51.h>

#define		LCD		P1	// D0 - D7 connected to P2.0 to P2.7
sbit rs = P1^1;
//sbit rw = P1^1;
sbit en = P1^0;

		

void delay(unsigned char); 
void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void lcd_init(void);
 void delay(unsigned char time)
{
int i,j;
for(j=0;j<time;j++)
for(i=0;i<1275;i++);
}

void lcd_init() 
{
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x0E);
lcd_cmd(0x80);
}
void lcd_data1(unsigned char value)
{
	LCD=value;
	rs=1;
//	rw=0;
	en=1;
	delay(5);
	en=0;
}
void lcd_data(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data1(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_data1(cd1);
}	

void lcd_cmd1(unsigned char value)
{
	LCD=value;
	rs=0;
	//rw=0;
	en=1;
	delay(5);
	en=0;
}
void lcd_cmd(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_cmd1(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_cmd1(cd1);
}	
 void lcd_str(unsigned char *s)
{
		while(*s!='\0')	// string not equal to null character
		{
			lcd_data(*s++);
		}
}  
void main()
 {
 unsigned char i=0,j=0,k=0, mybyte;
 unsigned char pos=0x80, ps=0xc0;
 LCD=0x00;
	    lcd_init();
TMOD=0x20; //use Timer 1, mode 2
TH1=0xFA; //4800 baud rate
SCON=0x50;
TR1=1; //start timer
 lcd_str("welcome to auto");
 delay(15);
lcd_cmd1(0xc0);
lcd_str("matic system");
delay(20);
lcd_cmd(0x01);
while (1) {        //repeat forever
while (RI==0); //wait to receive
mybyte=SBUF; //save value
lcd_cmd(0x10);
if(j<32)
{
if(k<16)
{
lcd_cmd(pos);
lcd_data(mybyte); //write value to port
k++;
pos++;
j++;
}
else if(k<32)
{
lcd_cmd(ps);
lcd_data(mybyte);
k++;
ps++;
j++;
}
}
else if(k>=32)
{
k=0;
j=0;
pos=0x80; 
ps=0xc0;
lcd_cmd(0X01);
}
RI=0;

}

}