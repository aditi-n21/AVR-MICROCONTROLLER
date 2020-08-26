 #include<reg51.h>
#define LCD P0

sbit RS=P2^0; //connect p3.0 to rs pin of lcd
sbit RW=P2^1; //connect p3.1 to en pin of lcd
sbit EN=P2^2; //connect p3.2 to en pin of lcd

sbit RED= P1^1;
sbit Yellow= P1^2;
sbit Green= P1^0;
//sbit mode4= P2^3;
sbit led_red=P3^3;
sbit led_yellow=P3^2;
sbit led_green=P3^1;
sbit buzz=P3^0;
//sbit led4=P2^7;
sbit motor= P2^4;
//sbit motor=P2^0; 

void timer(unsigned char);
void variation(void);
void delay_ms(unsigned int);
void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
unsigned char keysense(void);


unsigned char pwm_width;
bit pwm_flag = 0;

void timer0() interrupt 1 {
        if(!pwm_flag) { //Start of High level
                pwm_flag = 1;   //Set flag
                motor = 1;     //Set PWM o/p pin
                TH0 = pwm_width;        //Load timer
                TF0 = 0;                //Clear interrupt flag
                return;         //Return
        }
        else {  //Start of Low level
                pwm_flag = 0;   //Clear flag
                motor = 0;     //Clear PWM o/p pin
                TH0 = 255 - pwm_width;  //Load timer
                TF0 = 0;        //Clear Interrupt flag
                return;         //return
        }
}

void main()
{
  unsigned char k;  
 //TMOD=0x20;
  //TH1=0xd2;
  RED=Yellow=Green=1;
 TMOD = 0x00;
//        pwm_width = 200;
        EA = 1;
        ET0 = 1;
        TR0 = 1;
		init_lcd();
		cmd_lcd(0x80);
		display_lcd("WELCOME 2 AUTOMATIC");
		cmd_lcd(0xc0);
		display_lcd("TRAIN ENGINE");
		cmd_lcd(0x80);
		display_lcd("Made By:-");
		cmd_lcd(0xc0);
		display_lcd("Vaishali Chauhan");
 while(1)
 { 
   k=keysense();
   switch(k)
   {
   	case 1:  
	         led_red=0;led_yellow=1;led_green=1;
	 	     pwm_width = 00;
			 cmd_lcd(0x80);
		
			display_lcd("100 % SPEED ");


		 break;
	case 2:
   		   led_red=1;led_yellow=0;led_green=1;
  pwm_width = 126;
	buzz=0;
   cmd_lcd(0x80);
		display_lcd("50 % SPEED ");
delay_ms(10);
	buzz=1;
		 break;
   	case 3:
   		   led_red=1;led_yellow=1;led_green=0;
	 	  pwm_width = 255;
		  cmd_lcd(0x80);
		display_lcd("stop ");
 break;
 default:   //pwm_width = pwm_width-40;
  //buzz=0;
 // led_red=1;led_yellow=1;led_green=1;
	 	 
	//	cmd_lcd(0x80);
		//display_lcd("100 % SPEED ");
//buzz=1;
			 break;
   }
 } 
}
unsigned char keysense(void)
{
if(RED==0)
   return(1);
else if(Yellow==0)
   return(2);
else if(Green==0)
   return(3);
//else if(mode4==0)
 //  return(4);
else
    return(0);

}
/*void timer(unsigned char msec)	 // Function for timer
{
	unsigned char i;
	TR1=1;
	for(i=0;i<msec;i++)
	{
		while(TF1==0);
		TF1=0;
	}
	TR1=0;
} */
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