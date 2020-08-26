#inlcude<reg51.h>
#define led p0
void delay (unsigned int msec)
void main()
{
unsigned char i;
led=0x01;
while(1)
{
for(i=0;i<8;i++)
{
led=<<led;
delay(100);
}
}
}
void delay(unsigned int msec)
{
unsigned int i,j;
for(i=0;i<msec;i++)
{
for(j=0;j<1275;j++)
}
}
