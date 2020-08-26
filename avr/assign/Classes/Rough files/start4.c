#include<reg51.h>
sbit led = P1^1;
void delay(unsigned char msec);
void main()
{
  while(1)
  {
  led=0;
  delay(100);
  led=1;
  delay(100);
  }

}
void delay(unsigned char msec)
{
  unsigned int i,j;
  for(i=0;i<msec;i++)
    for(j=0;j<1275;j++);
}