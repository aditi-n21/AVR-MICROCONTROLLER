// Program to test serial communication of controller with PC using hyper terminal
#include<reg51.h>

void ini()     // Initialize Timer 1 for serial communication
{
TMOD=0x20;  //Timer1, mode 2, baud rate 9600 bps
TH1=0XFD; 
SCON=0x50;
TR1=1;
}

void recieve()  //Function to receive serial data
{
unsigned char value;
while(RI==0);
value=SBUF;
if(value=='A')
{
P3=0x01;
}
else
if(value=='B')
{
P3=0x02;
}
else
if(value=='C')
{
P3=0x04;
}
//P1=value;
RI=0;
}

/*void transmit()  // Funtion to transmit serial data
{
P2=P1-32;
SBUF=P2;
while(TI==0);
TI=0;
SBUF=P1;
while(TI==0);
TI=0;
}*/

void main()
{
while(1)
{
  ini();
  recieve();
  //transmit();
}
}