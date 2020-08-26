#include<reg51.h>
sbit sense=P1^1;
sbit motor1=P1^3;
sbit motor2=P1^4;
void main()
{  sense=1;

   while(1)
   {
	if(sense==1)
	  {
	   motor1=1;
	   motor2=0;
	   }
	 else
	 {
	  motor1=0;
	   motor2=1;
	   }
	
	}
}