 #include<reg51.h>
#include<string.h>
 void delay();
sbit green= P1^0;
sbit red= P1^1;
sbit yellow= P1^2;
sbit motor= P2^4;
sbit objects= P2^1;
sbit gates=P2^0;
sbit motorg1=P2^6;
sbit motorg=P2^7;
sbit buzz=P3^0;
sbit sig=P1^7;
sbit intp= P3^2;
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
void extint() interrupt 0
{
	pwm_width=10;
}
void main()
{
//  unsigned char k;  
   objects=gates=green=red=yellow=1;
	buzz=1;
	intp=1;
	 TMOD = 0x02;
        EA = 1;
        ET0 = 1;
        TR0 = 1;
		EX0=1;
		motorg=0;
		motorg1=0;
		pwm_width=10;
		sig=1;
	 while(1)
 	{ 
   		if(green==0)
		pwm_width=240;
		if(yellow==0)
		pwm_width=120;
		if(red==0)
		pwm_width=10;  
		if(objects==1)
		pwm_width=10; 
		if(gates==1) 
		{
			motorg=1;
			motorg1=0;
			delay();
			delay();
			delay();
			delay();
			motorg=0;
			motorg1=1;
			delay();
			motorg=0;
			motorg1=0;
		}
	  /*k=keysense();
   switch(k)
   {
 	case 1:  
		     pwm_width = 10;
		 break;
	case 2:
     pwm_width = 100;
	buzz=0;
		 break;
	case 3:		 
	pwm_width = 250; break;
    default:   
			 break;
   }	*/

 	} 
}

unsigned char keysense(void)
{
 if(red==0)
   return(1);
    if(objects==1)
   return(1);
else if(yellow==0)
   return(2);
   else if(green==0)
   return(3);
else
	  return (0);
}
void delay()
{
	unsigned int i;
	for(i=0;i<65535;i++);
}
