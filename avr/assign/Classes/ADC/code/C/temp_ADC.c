#include<reg51.h>
#include<string.h>


							//to indicate working status
sbit EN = P2^7;
sbit RW=P2^6;								//for lcd
sbit RS = P2^5;								//for lcd								

sbit wr = P3^1;
sbit rd = P3^0;	
sbit intr = P3^2;


void delaylcd(unsigned int itime);			 //for lcd delay
void msdelay(unsigned int);					 //for long delay
void writecmd(unsigned char);				 //for lcd command mode
void writedata(unsigned char);				 //for lcd data mode
void writestr(unsigned char *s);			 //for string display
void lcd(void);								 //for lcd to give instructions
void temp();								 //for temperature 
void convertAndDisplay(unsigned char value);


void delaylcd(unsigned int itime)
{
	int i,j;
	for(i=0;i<itime;i++)
		for(j=0;j<1275;j++);
}

void msdelay(unsigned int value)
{
	unsigned int x,y;
	for(x=0;x<value;x++)
		for(y=0;y<325;y++);
}  
  
void writecmd(unsigned char a)
{
	RS=0;
	P0=a;
	EN=1;
	delaylcd(5);
	EN=0;
	return;
}

void writedata(unsigned char b)
{
	RS=1;
	P0=b;
	EN=1;
	delaylcd(5);
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
  
void lcd()
{
	writecmd(0x38);
	writecmd(0x0c);
	//writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
	
}


void temp() 
{	  unsigned char value;
	   
	      delaylcd(5);
		   wr = 0;
		  delaylcd(5);
		  wr = 1;
	  	  while(intr==1);
		  rd=1;
		  rd=0;
		  value = P1;	
		  convertAndDisplay(value);
		  rd=1;
}
	
void convertAndDisplay(unsigned char value)
	 
	 {
	  
	
	 unsigned char d1,d2;
		d1=value/10;
		d2=value%10;
	//	d3=x%10;
		writecmd(0xc3);
  		writestr("TEMP:");
		writecmd(0xc9);
		writecmd(0x06);
		writecmd(0x0E);
		writedata(d1+48);		
	//	MSdelay(50);
		writedata(d2+48);
	//	MSdelay(50);
	//	writedata(d3+48);
  		writedata('`');
  		writedata('C');
}	
void main()
{
  lcd();
  while(1)
  {
  temp();
  msdelay(10);
}
}		   