#include<reg51.h>

#define dtmf P0
#define LCD P1

sbit RS=P2^5; //connect p3.0 to rs pin of lcd
sbit RW=P2^6; //connect p3.1 to en pin of lcd
sbit EN=P2^7; //connect p3.2 to en pin of lcd

sbit r1=P2^0;
sbit r2=P2^1;
sbit r3=P2^2;
sbit r4=P2^3;
sbit test=P2^4;

void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
void delay_ms(unsigned int);

void main()
{
   dtmf=0xff;
   test=1;
  init_lcd();
  display_lcd("Welcome To HOME");
   cmd_lcd(0xc0);
  display_lcd("Automation using ");
delay_ms(200);
	cmd_lcd(0x01);
  display_lcd(" Bluetooth>>>>>> ");
 cmd_lcd(0xc0);
  display_lcd("   MADE BY:-");	
	delay_ms(200);
	cmd_lcd(0x01);
  display_lcd("SAKSHI, VAISHALI");
	
 cmd_lcd(0xc0);
  display_lcd("NEELAM & SHIPRA");	
	
	delay_ms(200);
		cmd_lcd(0x01);

	while(1)
  {
		if(test==1)
		{ 
				if(dtmf==0xf8)
	     {
		  r1=1;
				 delay_ms(10);
				 		cmd_lcd(0x80);
					  display_lcd("   RELAY 1     ");	

				// r2=0;r3=0;r4=0;
		 }
  	else if(dtmf==0xf4)
	     {
		  //r1=0;
				 r2=1;
				 cmd_lcd(0x80);
					  display_lcd("   RELAY 2     ");	

				 //r3=0;r4=0;
		 }
	else if(dtmf==0xfc)
	     {
 
		  //r1=0;r2=0;
				 r3=1;
				 cmd_lcd(0x80);
					  display_lcd("   RELAY 3     ");	

				// r4=0;
		 }
	else if(dtmf==0xf2)
	     {
		//  r1=0;r2=0;r3=0;
				 r4=1;
				 cmd_lcd(0x80);
					  display_lcd("   RELAY 4     ");	

		 }
	else if(dtmf==0xfa)
	     {
		  r1=1;r2=1;r3=1;r4=1;
			 cmd_lcd(0x80);
					  display_lcd("   RELAY ON    ");	

		 }
   	else if(dtmf==0xf5)
	     {
		  r1=0;r2=0;r3=0;r4=0;
 cmd_lcd(0x80);
					  display_lcd("   RELAY OFF    ");	
		 
}
else
{ 
			cmd_lcd(0x80);
 display_lcd("  Scanning Signal  ");
 	cmd_lcd(0xc0);
 display_lcd("                ");
 
}
}
else
{
					cmd_lcd(0x80);
 display_lcd(" External Supply ");
			cmd_lcd(0xc0);
 display_lcd(" Not Connected  ");
delay_ms(200);

}
  }
}

//initialize lcd
void init_lcd(void)
{                           
cmd_lcd(0x0e); //lcd on, cursor on
delay_ms(10);
cmd_lcd(0x38); //8 bit initialize, 5x7 character font, 16x2 display
delay_ms(10);
cmd_lcd(0x06); //right shift cursor automatically after each character is displayed
delay_ms(10);
cmd_lcd(0x01); //clear lcd
delay_ms(10);
cmd_lcd (0x80);
}
void delay_ms(unsigned int i)
{
unsigned int j;
            while(i-->0)
            {
                        for(j=0;j<500;j++)
                        {
                                    ;
                        }
            }
}           

//transmit command or instruction to lcd
void cmd_lcd(unsigned char c)
{
EN=1;
RW=0;//set enable pin
RS=0; //clear register select pin
LCD=c; //load 8 bit data
EN=0; //clear enable pin
delay_ms(2); //delay 2 milliseconds
}
//transmit a character to be displayed on lcd
void write_lcd(unsigned char c)
{
EN=1; //set enable pin
RW=0;
RS=1; //set register select pin
LCD=c;  //load 8 bit data
EN=0; //clear enable pin
delay_ms(2); //delay 2 milliseconds
}
//transmit a string to be displayed on lcd
void display_lcd(unsigned char *s)
{
while(*s)
write_lcd(*s++);
}