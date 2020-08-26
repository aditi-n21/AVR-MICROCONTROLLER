#include<reg51.h>
sbit mot1_A=P2^0;
sbit mot1_B=P2^1;
sbit mot2_A=P2^2;
sbit mot2_B=P2^3;

void main()
{
  while(1)
  {
  	mot1_A=1;
	mot1_B=0;		 // clockwise
  	  	mot2_A=0;
	mot2_B=1;		  //anticlockwise
    

  }

}