#include<reg51.h>
void trans(unsigned char send);
void delay(unsigned char msec);
unsigned char recv(void);
void main()
{
  unsigned char k;
  SCON=0x50;
  TMOD=0x20;
  TH1=0xfd;
  TR1=1;
while(1)
{
    k=recv();
	trans(k);
	delay(10);
}
}

void trans(unsigned char send)
{
SBUF=send;
while(TI==0);
TI=0;
}
unsigned char recv(void)
{
RI=0;
while(RI==0);
return SBUF;
}
void delay(unsigned char msec)
{
unsigned char i;
unsigned int j;
for(i=0;i<msec;i++)
 for(j=0;j<1275;j++);
}
