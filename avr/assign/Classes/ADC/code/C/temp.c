#include<reg51.h>
#include<math.h>


#define adc_input P1
#define dataport P0
#define sec 100
sbit rs = P2^4;
sbit rw = P2^5;
sbit e = P2^6;

sbit wr= P3^7;
sbit rd= P3^6;
sbit intr=P3^5;

void convertAndDisplay(unsigned char value);
void MSdelay(unsigned int value);
void lcd(void);
void writecmd(unsigned char);
void writedata(unsigned char);
void delay(unsigned int);
void writestr(unsigned char *s);


//int test_intermediate3=0, test_final=0,test_intermediate1[10],test_intermediate2[3]={0,0,0};

void delay(unsigned int msec )
{
int i ,j ;
for(i=0;i<msec;i++)
  for(j=0; j<1275; j++);
}

void writecmd(unsigned char item)  //Function to send command to LCD
{
dataport = item;
rs= 0;
rw=0;
e=1;
delay(1);
e=0;
return;
}

void writedata(unsigned char item) //Function to send data to LCD
{
dataport = item;
rs= 1;
rw=0;
e=1;
delay(1);
e=0;
//delay(100);
return;
}

void writestr(unsigned char *str)  // Function to send string to LCD
{
int i=0;
while(str[i]!='\0')
{
  writedata(str[i]);
  i++;
  delay(10);
}
return;
}


/*void delaylcd(unsigned char a)
{
  int i,j;
  for(i=0;i<a;i++)
  		for(j=0;j<1275;j++);
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

void writecmd(unsigned char a)
{
	RS=0;
	P0=a;
//	RW=0;
	EN=1;
	delaylcd(5);
	EN=0;
	return;
}

void writedata(unsigned char b)
{
	RS=1;
	P0=b;
//	RW=0;
	EN=1;
	delaylcd(5);
	EN=0;
	return;
} */
void lcd(void)
{
	writecmd(0x38);
	writecmd(0x0c);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
}

	

void convertAndDisplay(unsigned char value)
	 {
	   /* unsigned char x,d1,d2,d3;
		x=value/10;
		d1=value%10;
		d2=x%10;
		d3=x%10;
		writecmd(0x86);
		writecmd(0x0E);
		writedata(d1);		
		MSdelay(50);
		writedata(d2);
		MSdelay(50);
		writedata(d3);
		MSdelay(50); 	   */
	 unsigned char x=0,b=0,n=0,i;
  		unsigned int len[8], sum = 0;
 
  for(i=0;i<=7;i++)
  {	x=value/10;
    b=value%10;
	value=value/10;
    len[i]= b;
  }
  for(i=0; i <= 7; i++) 
  {
     n=len[i]*pow(2,i);
     sum = sum + n;
    }
  lcd();
  writestr("TEMP:");
  x=sum/10;
  b=sum%10;
  writecmd(0xc8);
    writedata(x+48); 
	writecmd(0x06);
  writedata(b+48);
  // MSdelay(50);
   /*int s,tf=0;
tf=value;
writecmd(0xc1); 			//force lcd to start with IInd line c1 position
delay(2);
writestr("TEMP:");
s=tf/100;
tf=tf%100;
writecmd(0xc6);		   //force lcd to start with IInd line c8 position
if(s!=0)
writedata(s+48);
else
{writecmd(0x06);
 s=tf/10;
 tf=tf%10;
 writedata(s+48);
 }
writedata(tf+48);
writedata('"');
writedata('c');
//writedata(' ');							 
//MSdelay(2); */

}			   
	
void MSdelay(unsigned int value)
	{
	   unsigned char x,y;
	   for(x=0;x<value;x++)
	    for(y=0;y<1275;y++);
	}
void main()
	{
	   unsigned char value;
	   P1 =0xFF;
	   //intr = 1;
	  	rd = 1;
	 	 wr = 1;
	   lcd();
	   writestr("PROJECT");
	   
	   while(1)
	   {
	      delay(5);
		   wr = 0;
		  delay(5);
		  wr = 1;
		  lcd();
	   writestr("ON");
	   
	   	  while(intr==1);
		rd=0;
		  lcd();

	   writestr("TEMPERATURE");
	   	 
		  value = P1;	
		  convertAndDisplay(value);
		  rd=1;
		  }
	 }
 