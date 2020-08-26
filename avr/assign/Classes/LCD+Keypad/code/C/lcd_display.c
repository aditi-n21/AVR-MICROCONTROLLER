#include<reg51.h>
#include<string.h>

sbit RS=P3^3;
sbit RW=P3^4;
sbit EN=P1^7;
sbit row1=P3^0;
sbit row2=P3^1;
sbit row3=P3^2;
sbit row4=P2^3;
sbit col1=P3^5;
sbit col2=P3^6;
sbit col3=P3^7;

void lcd(void);
void writecmd(unsigned char);
void writedata(unsigned char);
void delaylcd(unsigned char);
void writestr(unsigned char *s);
void msdelay(unsigned int value);
unsigned char keysense(void);

void delaylcd(unsigned char a)
{
  int i,j;
  for(i=0;i<a;i++)
  		for(j=0;j<1275;j++);
}

unsigned char keysense(void)
{
	while(1)
	{
		col1=0;
		col2=1;
		col3=1;
		if(row1==0)	
			return(1);
		if(row2==0)
			return(4);
		if(row3==0)
			return(7);
		if(row4==0)
			return('*');
		col1=1;
		col2=0;
		col3=1;
		if(row1==0)
			return(2);
		if(row2==0)
			return(5);
		if(row3==0)
			return(8);
		if(row4==0)
			return(0);		
		col1=1;
		col2=1;
		col3=0;
		if(row1==0)
			return(3);
		if(row2==0)
			return(6);
		if(row3==0)
			return(9);
		if(row4==0)
			return('#');
		msdelay(50);
	};
}	 

void msdelay(unsigned int value)
{
	unsigned int x,y;
	for(x=0;x<value;x++)
		for(y=0;y<325;y++);
}  
void writestr(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		writedata(*s);
		s++;
		msdelay(50);
	}
}

void writecmd(unsigned char a)
{
	RS=0;
	P0=a;
	RW=0;
	EN=1;
	delaylcd(5);
	EN=0;
	return;
}

void writedata(unsigned char b)
{
	RS=1;
	P0=b;
	RW=0;
	EN=1;
	delaylcd(5);
	EN=0;
	return;
}
void lcd(void)
{
	writecmd(0x38);
	writecmd(0x0e);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
}

void main()
{
	unsigned char a;
	char arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	 	lcd();
	 writestr("WELCOME");
	writecmd(0xc5);
	writestr("	  CETPA");
	writecmd(0x01);
/*	writestr("MANOJ");
	writecmd(0xc5);
	writestr("KUMAR");
	writecmd(0x01);
	writestr("KEY SENSED");	
	writecmd(0xc6);
	writedata('A');
	keysense();		 */
 
	while(1)
	{
	 writecmd(0x80);
	writestr("KEY SENSED");	
	
	a=keysense();
	switch(a)
	{
   case 0: 
		P0=arr[a];
		//	msdelay(10);
			writecmd(0xc5);
			writestr("KEY 0");
			msdelay(50);
			break;
	case 1: writecmd(0xc5);
		P0=arr[a];
			//msdelay(10);
			writestr("KEY 1");
			msdelay(50);
			break;
	case 2: writecmd(0xc5);
		P0=arr[a];
			//msdelay(10);
			writestr("KEY 2");
			msdelay(50);
			break;
    case 3: writecmd(0xc5);
			P0=arr[a];
			//msdelay(10);
			writestr("KEY 3");
			msdelay(50);
			break;
	case 4:  writecmd(0xc5);
			P0=arr[a];
			//msdelay(10);
			writestr("KEY 4");
			msdelay(50);
			break;
	case 5:   writecmd(0xc5);
			P0=arr[a];
			//msdelay(10);
			writestr("KEY 5");
			msdelay(50);
			break;
	case 6:  writecmd(0xc5);
			P0=arr[a];
			//msdelay(10);
			writestr("KEY 6");
			msdelay(50);
			break;
	case 7:  writecmd(0xc5);
			P0=arr[a];
			//msdelay(10);
			writestr("KEY 7");
			msdelay(50);
			break;
	case 8:  writecmd(0xc5);
			P0=arr[a];
			writestr("KEY 8");
			msdelay(50);
			break;
	case 9: writecmd(0xc5);
			P0=arr[a];
			writestr("KEY 9");
            msdelay(50);
			break;
	default:
			break;

}
     }

}


