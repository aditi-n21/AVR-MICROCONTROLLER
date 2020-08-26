#include<reg51.h>
#include<string.h>

sbit red= P1^0;
sbit green= P1^1;
sbit yellow= P1^2;
sbit motor= P2^4;
sbit buzz=P1^3;

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
   green=red=yellow=1;
	buzz=1;
	 TMOD = 0x02;
        EA = 1;
        ET0 = 1;
        TR0 = 1;
	 while(1)
 { 
   k=keysense();
   switch(k)
   {
 	case 1:  
		     pwm_width = 10;
	buzz=1;
		 break;
	case 2:
     pwm_width = 100;
	buzz=0;
		 break;
    default:   pwm_width = 250;
		buzz=1;
			 break;
   }
 } 
}
unsigned char keysense(void)
{
 if(red==0)
   return(1);
else if(yellow==0)
   return(2);
else
	  return (0);
}
