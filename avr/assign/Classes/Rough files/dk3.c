#include<reg51.h>
#include<string.h>
#define seg P3
#define led P1
#define lcd P0

sbit row1=P2^0;
sbit row2=P2^1;
sbit row3=P2^2;
sbit col1=P2^3;
sbit col2=P2^4;
sbit col3=P2^5;
sbit rs=P2^6;
sbit en=P2^7;

void init_lcd(void);
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
	//	if(row4==0)
	//		return('*');
		col1=1;
		col2=0;
		col3=1;
		if(row1==0)
			return(2);
		if(row2==0)
			return(5);
		if(row3==0)
			return(8);
	//	if(row4==0)
	//		return(0);		
		col1=1;
		col2=1;
		col3=0;
		if(row1==0)
			return(3);
		if(row2==0)
			return(6);
		if(row3==0)
			return(9);
	//	if(row4==0)
	//		return('#');
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
	rs=0;
	lcd=a;
	//rw=0;
	en=1;
	delaylcd(5);
	en=0;
	return;
}

void writedata(unsigned char b)
{
	rs=1;
	lcd=b;
	//rw=0;
	en=1;
	delaylcd(5);
	en=0;
	return;
}
void init_lcd(void)
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
 	init_lcd();
	P2=0x07;
	while(1)
	{
	 writecmd(0x80);
	writestr("KEY SENSED");	
	a=keysense();
	switch(a)
	{
      /* case 0: 
	    	seg=arr[a];
			writecmd(0xc5);
			writestr("KEY 0");
			led=0xff;
			msdelay(50);
			break;	 */
	case 1: 
	       writecmd(0xc5);
		   seg=arr[a];
			writestr("KEY 1");
			led=0xfe;
			msdelay(50);
			break;
	case 2: writecmd(0xc5);
		    seg=arr[a];
			writestr("KEY 2");
			led=0xfd;
			msdelay(50);
			break;
    case 3: writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 3");
			led=0xfc;
			msdelay(50);
			break;
	case 4:  writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 4");
			led=0xfb;
			msdelay(50);
			break;
	case 5:   writecmd(0xc5);
			  seg=arr[a];
			writestr("KEY 5");
			led=0xfa;
			msdelay(50);
			break;
	case 6:  writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 6");
			led=0xf9;
			msdelay(50);
			break;
	case 7:  writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 7");
			led=0xf8;
			msdelay(50);
			break;
	case 8:  writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 8");
			led=0xf7;
			msdelay(50);
			break;
	case 9: writecmd(0xc5);
			seg=arr[a];
			writestr("KEY 9");
			led=0xf6;
            msdelay(50);
			break;
	default:
			break;

}
     }

}


