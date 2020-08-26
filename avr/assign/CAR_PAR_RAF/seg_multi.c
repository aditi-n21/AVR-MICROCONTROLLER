#include<reg51.h>
void timer_ini();
void delay(); 
void delay2();
void delay1();
void lcd_data(unsigned char);
void lcd_com(unsigned char );
void comn_data(unsigned char,unsigned char *);
void lcd_ini();
unsigned char opt=1;
#define s1 P1
#define lcd P2
sbit rs=P0^2;
sbit rw=P0^3;
sbit en=P0^4;
sbit seg1= P3^2;
sbit seg2= P3^3;
sbit sw1= P0^0;
sbit sw2= P0^1;
unsigned char dat1=0xa4,dat2=0xc0;
void main()
{
	unsigned char ar[]={0xc0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	unsigned char max=20,low,up;
	IE=0x82;
	timer_ini();
	lcd_ini();
		comn_data(0x80,"Car space ");
	comn_data(0xc4,"available");
	while(1)
	{
		if(sw1==1)
		{
		 while(sw1==1);
			if(max!=20)
			max++;
			//seg=ar[i];
			low=max/10;
			up=max%10;
			dat1=ar[low];
			dat2=ar[up];
			if(max>0)
			{
			comn_data(0x80,"Car space ");
			comn_data(0xc4,"available");	
			}
		}
		if(sw2==1)
		{
		 while(sw2==1);
			if(max!=0)
			max--;
			low=max/10;
			up=max%10;
			dat1=ar[low];
			dat2=ar[up];
			if(max==0)
			{
			comn_data(0x80,"No space ");
			comn_data(0xc4,"available");	
			}
		}
	}
}
void timer_ini()
{
	TMOD=0x01;
	TH0=0x60;
	TL0=0x00;
	TR0=1;
}
void delay()
{
	unsigned int i,j;
	for(i=0;i<1;i++)
	for(j=0;j<65535;j++);
}
void timer0() interrupt 1
{

	switch(opt)
	{
		case 1:

				P3=0x00;
				seg1=1;
				s1=dat2;
		break;
		case 2:
				
				P3=0x00;
				seg2=1;
				s1=dat1;
		break;	
	}
	opt++;
	if(opt==3)
	 opt=1;
	TH0=0xd0;								  //value of 80<TH0<d0
	TL0=0x00;
}
void lcd_ini()
{
	lcd_com(0x38);
	lcd_com(0x0e);
	lcd_com(0x01);
	lcd_com(0x06);
	lcd_com(0x80);
}
void lcd_com(unsigned char com)
{
	lcd=com;
	rs=0;
	rw=0;
	en=1;
	delay2();
	en=0;
	delay1();
	
}
void lcd_data(unsigned char dat)
{
	lcd=dat;
	rs=1;
	rw=0;
	en=1;
	delay2();
	en=0;
	delay1();
}
void comn_data(unsigned char com ,unsigned char *dat)
{
	lcd_com(com);
	while(*dat)
	{
		lcd_data(*dat++);
	}	
}
void delay2()
{
	unsigned char i;
	for(i=0;i<255;i++);
}
void delay1()
{
	unsigned int i,j;
	for(i=0;i<6553;i++);
}
