#include<reg51.h>

void _nop_(void);

#define delay_us _nop_(); //generates 1 microsecond
#define LCD P2
#define ADC_OUT P1
sbit RS=P3^4; //connect p3.0 to rs pin of lcd
sbit EN=P3^6; //connect p3.2 to en pin of lcd
sbit RW=P3^5; //connect p3.1 to en pin of lcd

sbit intr = P3^3;
sbit wr = P3^2;
sbit rd = P3^1;
sbit fan=P3^0;
sbit led1=P0^3;
sbit led2=P0^4;
sbit led3=P0^5;
sbit led4=P0^6;


void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
void delay_ms(unsigned int);
void temp();								 //for temperature 
void convertAndDisplay(unsigned char value);
void timer(unsigned char);
void temp_check(unsigned char);
unsigned char pwm_width;
bit pwm_flag = 0;

void main()
{
	        pwm_width = 160;
        EA = 1;  //Enable Interrupt
        ET0 = 1;  // enable Timer interrupt
        TR0 = 1;    //Start Timer	
    TMOD=0x02;
	//TH1=0xd2;
	init_lcd();
	cmd_lcd(0x82);
	display_lcd("TEMP:");
   while(1)
   {
   	temp();  
   }
}



void timer0() interrupt 1 {
       	 // Function for timer

	unsigned char i;
	TR0=1;
	for(i=0;i<10;i++)
	{
		while(TF0==0);
		TF0=0;
	}
	TR0=0;

}

void temp() 
{	  unsigned char value;
	       delay_ms(1);
		   wr = 0;
		  delay_ms(1);
		  wr = 1;
	  	  while(intr==1);
		  rd=0;
		  value = ADC_OUT;
			value=value*2;
		  convertAndDisplay(value);
		  rd=1;
}
	
void convertAndDisplay(unsigned char value)
	 
	 {
	    unsigned char x,d1,d2;
		x=value/10;
		d1=value%10;
		d2=x%10;
	//	d3=x%10;
				cmd_lcd(0x88);
		//cmd_lcd(0x06);
		//cmd_lcd(0x0E);
		write_lcd(d2+48);		
		write_lcd(d1+48);
		write_lcd('`');
  		write_lcd('C');
		delay_ms(10);
		temp_check(value);
		
}
void temp_check(unsigned char value)
{
	
	if(value<=25)
	 {	 led1=0;led2=1;led3=1;led4=1;
	 			 pwm_width=250;
		 //cmd_lcd(0x01);
		 cmd_lcd(0xc4);
		 display_lcd("MODE 1");
		 delay_ms(10);
	 }
	else if((value>25)&&(value<=30))
	 {
	 led1=1;led2=0;led3=1;led4=1;
	 	// fan=1;
		// timer(50);
		 //delay_ms(10);
		 //fan=0;
		 //timer(50);
		  pwm_width=190;
		// cmd_lcd(0x01);
		  cmd_lcd(0xc4);
		 display_lcd("MODE 2");
		
		 delay_ms(10);
	 }
	 else if((value>30)&&(value<=35))
	 {
	 	 led1=1;led2=1;led3=0;led4=1;
		// fan=1;
		 //timer(75);
		 //delay_ms(10);
		 //fan=0;
		// timer(25);
		 pwm_width=130;
	//	 cmd_lcd(0x01);
		 cmd_lcd(0xc4);
		 display_lcd("MODE 3");
		
		 delay_ms(10);
	 }
	 else if((value>35)&&(value<=40))
	 {
	 	 led1=1;led2=1;led3=1;led4=0;
		// fan=1;
		 //timer(75);
		 //delay_ms(10);
		 //fan=0;
		// timer(25);
		 pwm_width=70;
	//	 cmd_lcd(0x01);
		 cmd_lcd(0xc4);
		 display_lcd("MODE 4");
		
		 delay_ms(10);
	 }
	 else
	 {
	 	 led1=0;led2=0;led3=0;led4=0;
		// fan=1;
		// timer(100);
		 pwm_width=10;
	//	 cmd_lcd(0x01);
		cmd_lcd(0xc4);
		 display_lcd("MODE 5");
		 delay_ms(10);
	}
	 
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
