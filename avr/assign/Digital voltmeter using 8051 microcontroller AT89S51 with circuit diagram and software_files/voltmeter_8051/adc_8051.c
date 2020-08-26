#include<reg51.h>
void _nop_(void);

#define delay_us _nop_(); //generates 1 microsecond
#define LCD P2
#define ADC_OUT P1
sbit RS=P3^0; //connect p3.0 to rs pin of lcd
sbit RW=P3^1; //connect p3.2 to en pin of lcd
sbit EN=P3^2; //connect p3.1 to en pin of lcd

sbit rd = P3^3;
sbit wr = P3^4;
sbit intr = P3^5;

void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
void delay_ms(unsigned int);
void temp();								 //for temperature 
void convertAndDisplay(unsigned int value);
void timer(unsigned char);
void temp_check(unsigned char);


void main()
{
    TMOD=0x20;
	init_lcd();
	cmd_lcd(0x82);
	display_lcd("TEMP:");
   while(1)
   {
   	temp();  
   }
}

void timer(unsigned char msec)	 // Function for timer
{
	unsigned char i;
	TR1=1;
	for(i=0;i<msec;i++)
	{
		while(TF1==0);
		TF1=0;
	}
	TR1=0;
}

void temp() 
{	 unsigned int value;
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

 /*void convertAndDisplay(unsigned int value)
	 
	 {
	    unsigned char x,d1,d2;
		value=value*2;
		d1=value%10;
		d2=value/10;
		cmd_lcd(0x88);
		write_lcd(d2+48);		
		write_lcd(d1+48);
		write_lcd('`');
  		write_lcd('C');
		delay_ms(10);
		
} */
  void convertAndDisplay(unsigned int value)	//func.   for voltage
	 
	 {
	    unsigned char x,d1,d2;
		float value1;
		value1=(float)value;
		value1=(value1*500)/255;
		value=(unsigned int)value1;
		d1=value%10;		//lsb
		d2=value/10;
		x=d2%10;
		d2=d2/10;	 //msb
		cmd_lcd(0x88);
		write_lcd(d2+48);
		write_lcd('.');		
		write_lcd(x+48);
		write_lcd(d1+48);
		delay_ms(10);
		
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
