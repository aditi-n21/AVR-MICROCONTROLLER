#include<reg51.h>

sbit rotor_a = P2^0;
sbit rotor_b = P2^1;
sbit rotor_c = P2^2;
sbit rotor_d = P2^3;
sbit red = P2^4;
sbit green = P2^5;

void stepperf(void);
void stepperb(void);
void delay(unsigned char);

void stepperf(void)
{
	unsigned int i;
	for(i=0;i<20;i++)
		{
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
		}
}
void stepperb(void)
{
	unsigned int i;
	for(i=0;i<20;i++)
		{
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
		}
}
void delay(unsigned char time)
{
int i,j;
for(j=0;j<time;j++)
for(i=0;i<1275;i++);
}
void main(void)
{
red=1;
green=1;
while(1)
{
red=0;
green=1;
stepperf();
red=1;
green=0;

stepperb();

}

}