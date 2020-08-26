 #include<reg51.h>
#define LCD P0

sbit RS=P3^0; //connect p3.0 to rs pin of lcd
sbit RW=P3^1; //connect p3.1 to en pin of lcd
sbit EN=P3^2; //connect p3.2 to en pin of lcd
sbit blue=P1^0;
sbit RED= P1^3;
sbit Yellow= P1^2;
sbit Green= P1^1;
//sbit mode4= P2^3;
sbit led_red=P3^4;
sbit led_yellow=P3^5;
sbit led_green=P3^6;
sbit led_blue=P3^7;

sbit buzz=P2^3;
//sbit led4=P2^7;
sbit motor= P2^4;
sbit motor2=P2^7; 

void delay(unsigned int);
void delay_ms(unsigned int);
void init_lcd(void);
void cmd_lcd(unsigned char);
void write_lcd(unsigned char);
void display_lcd(unsigned char *);
unsigned char keysense(void);


unsigned char pwm_width,cnt=0;
bit pwm_flag = 0;

void timer0() interrupt 1 {
        if(!pwm_flag) { //Start of High level
                pwm_flag = 1;   //Set flag
                motor = 1;     //Set PWM o/p pin
					  motor2=1;
                TH0 = pwm_width;        //Load timer
                TF0 = 0;                //Clear interrupt flag
                return;         //Return
        }
        else {  //Start of Low level
                pwm_flag = 0;   //Clear flag
                motor = 0;     //Clear PWM o/p pin
					       motor2=0;
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
  RED=Yellow=Green=blue=1;
 TMOD = 0x20;
	TH0=0x00;
	//motor=0;
      //  pwm_width = 250;
        EA = 1;
        ET0 = 1;
        TR0 = 1;
		init_lcd();
		cmd_lcd(0x80);
		display_lcd(" WELCOME TO SELF ");
		cmd_lcd(0xc0);
		display_lcd("    CONTROLLED ");
	delay(200);
	cmd_lcd(0x01);
	cmd_lcd(0x80);
		display_lcd("  LOCOMOTIVE   ");
		cmd_lcd(0xc0);
		display_lcd(" MADE BY:-");
		delay(200);
		cmd_lcd(0x01);
		cmd_lcd(0x80);
		display_lcd("ASHI,DEEPTI");
		cmd_lcd(0xc0);
		display_lcd("ADITYA & SANDEEP ");
delay(200);
cmd_lcd(0x01);
		cmd_lcd(0x80);
		display_lcd("FROM:-");
		cmd_lcd(0xc0);
		display_lcd("DIET, Rishikesh ");
delay(200);
	cmd_lcd(0x01);
 while(1)
 { 
   k=keysense();
   switch(k)
   {
   	case 1:  
	         led_red=0;led_yellow=1;led_green=1;led_blue=1;
	 	     pwm_width = 250;
		//cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("     stop     ");
		delay(100);
	cmd_lcd(0x01);
		 break;
	case 2:
   		   led_red=1;led_yellow=0;led_green=1;led_blue=1;
  pwm_width = 126;
	buzz=0;
	//cmd_lcd(0x01);
   cmd_lcd(0x80);
		display_lcd("    50 % SPEED  ");
delay_ms(100);
	buzz=1;
		cmd_lcd(0x01);
		 break;
   	case 3:
   		   led_red=1;led_yellow=1;led_green=0;led_blue=1;
	 	  pwm_width = 00;
		//cmd_lcd(0x01);
	  cmd_lcd(0x80);
		display_lcd("   100% SPEED ");
		delay(200);
	cmd_lcd(0x01);
 break;
		case 4: 
			  led_red=1;led_yellow=1;led_green=1;led_blue=0;
	 	     pwm_width = 250;
		//	  cmd_lcd(0x01);
		if(cnt==0)
		{
			cnt++;
			cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("RISHIKESH STATION");
			cmd_lcd(0xc5);
			display_lcd("STOP");
			delay(500);
			cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("NEXT STATION");
			cmd_lcd(0xc0);
			display_lcd("HARIDWAR");
			delay(500);
		}
		else if(cnt==1)
		{
			cnt++;
			cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("HARIDWAR STATION");
			cmd_lcd(0xc5);
			display_lcd("STOP");
			delay(500);
			cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("NEXT STATION");
			cmd_lcd(0xc0);
			display_lcd(" ROORKEE  ");
			delay(500);
		}
		else
		{
			cnt=0;
			cnt++;
				cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("ROORKEE STATION");
			cmd_lcd(0xc5);
			display_lcd("STOP");
			delay(500);
			cmd_lcd(0x01);
			 cmd_lcd(0x80);
		display_lcd("NEXT STATION");
			cmd_lcd(0xc0);
			display_lcd("SAHARANPUR");
			delay(500);
		}
			cmd_lcd(0x01);
break;
 default:  
			 break;
   }
 } 
}
void delay(unsigned int msec)
{
	unsigned int i,j;
  for(i=0;i<msec;i++)
	  for(j=0;j<1275;j++);
}
unsigned char keysense(void)
{
if(RED==0)
   return(1);
else if(Yellow==0)
   return(2);
else if(Green==0)
   return(3);
else if(blue==0)
   return(4);
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
cmd_lcd(0x38); //8 bit initialize, 5x7 character font, 16x2 display
delay_ms(5);
cmd_lcd(0x0e); //lcd on, cursor on
delay_ms(5);
cmd_lcd(0x06); //right shift cursor automatically after each character is displayed
delay_ms(5);
cmd_lcd(0x01); //clear lcd
delay_ms(5);
cmd_lcd (0x80);
	delay_ms(5);

}
//transmit command or instruction to lcd
void cmd_lcd(unsigned char c)
{
EN=1;
RW=0;//set enable pin
RS=0; //clear register select pin
LCD=c; //load 8 bit data
delay_ms(5); //delay 2 milliseconds
EN=0; //clear enable pin

}
//transmit a character to be displayed on lcd
void write_lcd(unsigned char c)
{
EN=1; //set enable pin
RW=0;
RS=1; //set register select pin
LCD=c;  //load 8 bit data
delay_ms(5); //delay 2 milliseconds	
EN=0; //clear enable pin
}
//transmit a string to be displayed on lcd
void display_lcd(unsigned char *s)
{
while(*s)
write_lcd(*s++);
}