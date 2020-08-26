#include<reg51.h>
#include<string.h>
#include<stdio.h>

#define LCD P1
sbit RS = P3^0;
sbit RW = P3^1;
sbit EN = P3^2;
sbit red = P3^3;
sbit green = P3^4;
sbit buzz = P3^5;
sbit row0 = P0^0;
sbit row1 = P0^1;
sbit row2 = P0^2;
sbit col0 = P0^3;
sbit col1 = P0^4;
sbit col2 = P0^5;
sbit octo1 = P0^6;
sbit octo2 = P0^7;
sbit rotor_a = P2^0;
sbit rotor_b = P2^1;
sbit rotor_c = P2^2;
sbit rotor_d = P2^3;

unsigned int input,ps1=1234,ps2=4567;

void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_str(unsigned char *);
void lcd_init(void);
unsigned char keysense(void);
void delay(unsigned char);
unsigned int insert(void);
unsigned char cardread(void);
void right(void);
void stepperf(void);
void stepperb(void);
//char arr[10] = {0x40,0x79,0x24,0x30,0x19,0x12,0x02,0x78,0x00,0x10};

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
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x0E);
lcd_cmd(0x80);
}
void lcd_cmd(unsigned char value) 
{
LCD=value;
RS=0;
RW=0;
EN=1;
delay(2);
EN=0;
}
void lcd_str(unsigned char *s)
{
	unsigned char l,j;
	l=strlen(s);
	for(j=0;j<l;j++)
		{
			lcd_data(*s);
			s++;
		delay(10);
		}
}
void lcd_data(unsigned char value) 
{
LCD=value;
RS=1;
RW=0;
EN=1;
delay(2);
EN=0;
}
unsigned int insert(void)
{	 	unsigned char t1,t2,t3,t4;
		lcd_init();
		lcd_str("Enter password");
		t1=keysense();
		lcd_cmd(0xc6);
		lcd_data('#');
		delay(100);
		t2=keysense();
		lcd_cmd(0xc7);
		lcd_data('#');
		delay(100);
		t3=keysense();
		lcd_cmd(0xc8);
		lcd_data('#');
		delay(100);
		t4=keysense();
		lcd_cmd(0xc9);
		lcd_data('#');
		delay(10);
		input=1000*t1+100*t2+10*t3+t4;
		return(input);
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
void stepperf(void)
{
	unsigned int i;
	for(i=0;i<30;i++)
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
	for(i=0;i<30;i++)
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
unsigned char cardread(void)
{
							
       if((octo1==0)&&(octo2==0))
			{
 			return('0');
			}
		else if((octo1==0)&&(octo2==1))
			{
			 return('1');
			
			}
		else if((octo1==1)&&(octo2==0))
			{
			 return('2');
                                                 
			}
		else 
			 return('3');
}


void main()
{
unsigned char a,cnt=0;
red=0;
green=1;
buzz=1;
delay(10);
P0=0x07;
lcd_init();
lcd_str("A PROJECT ON");
lcd_cmd(0xc0);
lcd_str("PASSWORD BASED");
delay(10);
lcd_cmd(0x01);
lcd_str("SECURITY SYSTEM");
lcd_cmd(0xc2);
lcd_str("USING CARD");
delay(10);
lcd_cmd(0x01);
lcd_str("MADE BY :-");
lcd_cmd(0xc2);
lcd_str("NEHA & SONIA");
delay(10);
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("Security System");
delay(10);
while(1)
{
	a=cardread();
	switch(a)
		{
		   case '0':
		  
			//lcd_cmd(0x01);
			lcd_cmd(0xc0);
          lcd_str("Insert Card"); 
		  delay(10);
				break;
			
		   case '1':
			 lcd_cmd(0x01);		
			 lcd_str("Welcome user 1");
			 delay(10);
		aa1:	 insert();
			 if(input==ps1)
			      {
				 right();
					}
			 else
			 	{
			lcd_cmd(0x01);
			lcd_str(" Wrong Password");
			buzz=0;
			red=1;
			delay(10);
			buzz=1;
			cnt++;
			if(cnt<=2)
			{
			 lcd_cmd(0xc0);
			 lcd_str(" ENTER IT AGAIN");
			 red=0;
			 goto aa1;
			}
			else
				{
				  lcd_cmd(0x01);
				  lcd_str("   3rd time");
				  lcd_cmd(0xc0);
				  lcd_str(" Wrong Password");
			      buzz=0;
				  delay(10);
				  lcd_cmd(0x01);
                  red = 0;
			   	  lcd_str(" System Exiting!!!!");
				  delay(10);
				  buzz=1;
					lcd_cmd(0x01);
				  lcd_cmd(0x80);
					lcd_str("Security System");
                  delay(10);
				  break;
				}
			}	 
			break;
		   case '2':
			 lcd_cmd(0x01);
			 lcd_str("Welcome user 2");
			 delay(10);
		aa:	 insert();
			 if(input==ps2)
			       right();
			 else
			{
			lcd_cmd(0x01);
			lcd_str(" Wrong Password");
			buzz=0;
			red=1;
			delay(10);
			buzz=1;
			cnt++;
			if(cnt<=2)
			{
			 lcd_cmd(0xc0);
			 lcd_str(" ENTER IT AGAIN");
			 red=0;
			 goto aa;
			}
			else
				{
				  lcd_cmd(0x01);
				  lcd_str("   3rd time");
				  lcd_cmd(0xc0);
				  lcd_str(" Wrong Password");
			      buzz=0;
				  delay(10);
				  lcd_cmd(0x01);
                  red = 0;
			   	  lcd_str(" System Exiting!!!!");
				  delay(10);
				  buzz=1;

				  lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("Security System");
					delay(10);

				  break;
				}
			}	 
			break;
		   case '3':	 
			lcd_cmd(0x01);	
			 lcd_str("  Invalid Card");
				delay(100);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("Security System");
			delay(10);

			 break;
		}
      cnt=0;  
}
}