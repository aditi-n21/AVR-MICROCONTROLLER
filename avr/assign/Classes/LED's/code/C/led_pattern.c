#include<reg51.h>
#define led P2
void delay(unsigned char);
void main()
{
  led=0x55;
  delay(200);
  led=0xaa;
  delay(200);

}
void delay(unsigned char itime)
{
unsigned char i;
unsigned int j;
for(i=0;i<itime;i++)
for(j=0;j<1275;j++);
}