#include<reg51.h>
#include<string.h>
#define dtmf P1
sbit motor= P2^0;

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
  dtmf=0xff;
	motor=0;
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
		     pwm_width = 5;

			 break;
	case 2:
     pwm_width = 85;

		 break;
	case 3:
		 pwm_width = 175;
		 break;
    default:   pwm_width = 250;
				 break;
   }
 } 
}
unsigned char keysense(void)
{
 if(dtmf==0xf7)
   return(1);
else if(dtmf==0xfb)
   return(2);
else if(dtmf==0xf3)
	  return(3);

else
	  return(0);
}
