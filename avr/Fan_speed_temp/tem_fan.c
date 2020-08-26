#include<reg51.h>
void _nop_(void);
#define delay_us _nop_(); //generates 1 microsecond
#define LCD P0
#define ADC_OUT P1
sbit RS=P2^5; //connect p3.4 to rs pin of lcd
sbit RW=P2^6; //connect p3.6 to en pin of lcd
sbit EN=P2^7; //connect p3.5 to en pin of lcd
sbit intr = P3^0;
sbit wr = P3^1;
sbit rd = P3^2;
void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
void delay_ms(unsigned int);
void temp();								 //for temperature 
void convertAndDisplay(unsigned int);
void main()
{
	init_lcd();
	display_lcd("FAN SPEED CONT.");
	cmd_lcd(0xc3);
	display_lcd("ACC. TO TEMP");
	delay_ms(100);
	cmd_lcd(0x01);
	cmd_lcd(0x82);
	display_lcd("TEMP:-");
   while(1)
   {
   	 temp();  
   }
}


void temp() 
{	  unsigned int value;
	    delay_ms(1);
		  wr = 0;
		  delay_ms(1);
		  wr = 1;
	  	while(intr==1);
		  rd=0;
		  value = ADC_OUT;	
		  convertAndDisplay(value);
		  rd=1;
}
	
void convertAndDisplay(unsigned int value)
{
	unsigned char D1,D2,D3,D4;
	value=value*2;  
	//D0 = (value/10000) + 48;
	D1 = (value/1000)%10 + 48;
	D2 = (value/100)%10 + 48;
	D3 = (value/10)%10 + 48;
	D4 = (value%10) + 48;

	cmd_lcd(0x8a);
	write_lcd(D4);
	cmd_lcd(0x89);
	write_lcd(D3);
	cmd_lcd(0x8b);
	display_lcd("'C");
		
}
//initialize lcd
void init_lcd(void)
{                           
delay_ms(10); //delay 10 milliseconds
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
//generates delay in milli seconds
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
