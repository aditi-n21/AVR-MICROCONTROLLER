#include<reg51.h>
int j,i=0;
unsigned char arr[]="Vipul Ror";
void main(void)
{
TMOD=0x20; //use Timer 1, mode 2
TH1=0xFA; //4800 baud rate
SCON=0x50;
TR1=1;
while(1)
{
for(i=0; i<10; i++) 
{
SBUF = arr[i]; //place value in buffer
while (TI==0);
   TI=0;
   SBUF = ' ';
   SBUF =  ' ';
   while(TI==0);
   TI=0;
   }
   for(j=0; j<30000; j++);
 }
   }