#include<reg51.h>
#include<string.h>
#include<stdio.h>

#define LCD P0
sbit rs = P0^2;
//sbit rw = P3^1;
sbit en = P0^3;
sbit red = P1^4;
sbit green = P1^5;
sbit buzz = P3^0;
sbit row0 = P2^2;
sbit row1 = P2^3;
sbit row2 = P2^4;
sbit col0 = P2^5;
sbit col1 = P2^6;
sbit col2 = P2^7;
sbit rs1=P1^2;
sbit en1=P1^3;
//sbit sense3=P1^2;
//sbit sense4=P1^3;
sbit rotor_a = P3^4;
sbit rotor_b = P3^5;
sbit rotor_c = P3^6;
sbit rotor_d = P3^7;

bit cake;

void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void lcd_init(void);
unsigned char keysense(void);
void delay(unsigned char);
unsigned int insert(void);
void right(void);
void stepperf(void);
void stepperb(void);
void enter(void);
//void ex_out(void);
void convertAndDisplay(unsigned int);
unsigned search(unsigned int);

unsigned char no=0;

struct detail
{
	 unsigned int cn,pwd;
}st[10];

void external0(void) interrupt 0 
{
      cake=0;
      enter();
	  //	no++;
}

void external1(void) interrupt 2  
{	   cake=1;
 enter();
      
    
}

unsigned search(unsigned int match)
{
   unsigned char i=1,ct=0;
   unsigned int k;
   lcd_cmd(0x01);
		 lcd_cmd(0x80);
		    lcd_data(no+48);		
			lcd_cmd(0x85);
			 convertAndDisplay(st[i].cn);
   while(i<=no)
	  {
	   	     
			lcd_cmd(0xc0);
		    lcd_data(i+48);		
			lcd_cmd(0xc5);
			 convertAndDisplay(st[i].pwd);


	   if(match==st[i].cn)
		 {
		  lcd_cmd(0x01);
		 lcd_cmd(0x80);
		    lcd_data(no+48);		
			lcd_cmd(0x85);
			 convertAndDisplay(st[i].cn);
		     
			lcd_cmd(0xc0);
		    lcd_data(i+48);		
			lcd_cmd(0xc5);
			 convertAndDisplay(st[i].pwd);
		  aa:lcd_cmd(0x01);
		    lcd_str(" Enter Password");
		    k=insert();
			if(k==st[i].pwd)
			   {
		 	   return 1;
			   }
			else
			   {
			    if(ct<3)
			   	{	lcd_cmd(0x01);
		        	lcd_str(" Wrong Password");
					lcd_cmd(0xc0);
		    	    lcd_str(" Enter it again");
					buzz=0;
					delay(20);
			    	ct++;
			   		 goto aa;
			    }
				else
				   {
				    ct=0;
					lcd_cmd(0x01);
		        	lcd_str("Forget Password");
					lcd_cmd(0xc0);
		    	    lcd_str("Contact Security");
					buzz=0;
					delay(500);
					break;
				   }
		        }
			}
	   else
	     {
		    i++;
		  }
	  }

	  return 0;
}

void convertAndDisplay(unsigned int value)
	 
	 {
	    unsigned char x,y,d1,d2,d3,d4;
		x=value/10;
		d1=value%10;
		d2=x%10;
     	y=x/10;
		 d3=y%10;
		 d4=y/10;
	    //lcd_cmd(0x88);
		//lcd_cmd(0x06);
		//lcd_cmd(0x0E);
		lcd_data(d4+48);		
		lcd_data(d3+48);
		lcd_data(d2+48);		
		lcd_data(d1+48);
		
		delay(250);
		
}
void delay(unsigned char time)
{
int i,j;
for(j=0;j<time;j++)
for(i=0;i<1275;i++);
}
unsigned char keysense(void)
{
while(1)
{
col0=0;
col1=1;
col2=1;
if(row0==0)
return(1);
if(row1==0)
return(4);
if(row2==0)
return(7);
col0=1;
col1=0;
col2=1;
if(row0==0)
return(2);
if(row1==0)
return(5);
if(row2==0)
return(8);
col0=1;
col1=1;
col2=0;
if(row0==0)
return(3);
if(row1==0)
return(6);
if(row2==0)
return(9);
delay(10);
};
}

void lcd_init() 
{
lcd_cmd(0x20);
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
	delay(2);
	en=0;
	delay(2);
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
//	rw=0;
	en=1;
	delay(2);
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
	unsigned char l,j;
	l=strlen(s);
	for(j=0;j<l;j++)
		{
			lcd_data(*s);
			s++;
		delay(5);
		}
}
unsigned int insert(void)
 {	 	
 		unsigned int input;
        unsigned char t1,t2,t3,t4;
		//lcd_init();
	//	lcd_str("Enter password");
		t1=keysense();
		lcd_cmd(0xc6);
		lcd_data(t1+48);
		delay(50);
		lcd_cmd(0xc6);
		lcd_data('#');
		t2=keysense();
		lcd_cmd(0xc7);
		lcd_data(t2+48);
		delay(50);
		lcd_cmd(0xc7);
		lcd_data('#');
		t3=keysense();
		lcd_cmd(0xc8);
		lcd_data(t3+48);
		delay(50);
		lcd_cmd(0xc8);
		lcd_data('#');
		t4=keysense();
		lcd_cmd(0xc9);
		lcd_data(t4+48);
		delay(50);
		lcd_cmd(0xc9);
		lcd_data('#');
		input=1000*t1+100*t2+10*t3+t4;
		return(input);
}
void enter(void)
{  unsigned int car_no;
    bit h;
    if(cake==0)
	{  no++;
	if(no<=9)
	{
	lcd_cmd(0x01);
	lcd_str("Enter Car No.");
	st[no].cn=insert();
	lcd_cmd(0x01);
	lcd_str(" Set Password");
	st[no].pwd=insert();
	lcd_cmd(0x01);
	 lcd_str("Barrier Opening");
	stepperf();
	lcd_cmd(0xc0);
	lcd_str("Ur WELCOME");
	lcd_cmd(0x01);
	 lcd_str("Barrier Closing");
	stepperb();
	lcd_cmd(0xc0);
	lcd_str("Barrier Closed");

	lcd_cmd(0x01);
	return;
	}
  else
    {
  	 lcd_cmd(0x01);
	 lcd_str("Parking Full ");
  
    }
    }
else
    { 
   	if(no>0)
	{ 
	lcd_cmd(0x01);
	lcd_str("Enter Car No.");
	car_no=insert();
	h=search(car_no);
	  if(h==1)
		{
			lcd_cmd(0x01);
			lcd_str("Barrier Opening");
			stepperf();
			lcd_cmd(0xc0);
			lcd_str("Ur WELCOME");
			lcd_cmd(0x01);
	 		lcd_str("Barrier Closing");
			stepperb();
			lcd_cmd(0xc0);
			lcd_str("Barrier Closed");
			no--;
		 }
	  else
	    {
	   	 lcd_cmd(0x01);
		lcd_str("Car Not Found");	   
	    }
	lcd_cmd(0x01);
		 
	return;
	}
   else
    {
  	 lcd_cmd(0x01);
	 lcd_str(" ~~STOP~~ ");
  	    buzz=0;
	   delay(500);
	 	lcd_cmd(0x01);  
    }
   }
}				
void stepperf(void)
{
	unsigned int i;
	for(i=0;i<10;i++)
		{
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
		}
}
void stepperb(void)
{
	unsigned int i;
	for(i=0;i<10;i++)
		{
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
		}
}
void right(void)
		{
		lcd_init();
		lcd_str("Correct Password");
		delay(10);
		lcd_init();
		lcd_str("Opening Door");
		green=0;
		red=0;
		stepperf();
 		lcd_cmd(0xc0);
		lcd_str("  Ur Welcome");
		delay(100);
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		lcd_str("Closing Door");
		delay(10);
		stepperb();
		delay(10);
		lcd_cmd(0xc0);
		lcd_str("Door Closed");
		delay(10);
		green=1;
		delay(10);
		red=0;
		delay(10);
		delay(10);
		lcd_cmd(0x80);
		lcd_str("Security System");
        delay(10);
       } 

void main()
{
 //unsigned char a=0,cnt=0,user=0;
//unsigned int ca,pw,ca2,pw2;

red=0;
P2=0x1c;
IE=0x85;
IP=0x01;
green=1;
buzz=1;
delay(10);
lcd_init();
cake = 0;   
while(1)
{
	/* st[0].cn=1;
	 st[0].pwd=2;
	 st1[0].cn=3;
	 st1[0].pwd=4;	*/


	lcd_str("  ##STOP## ");
lcd_cmd(0xc0);
lcd_str("Press Enter key");


}

}