#include <at89x52.h>

extern unsigned char digit1;
extern unsigned char digit2;
extern unsigned char digit3;
extern unsigned char digit4;
extern void timer_enable(void);
void main(void)
{

timer_enable();
while(1){
digit1=0x00;
digit2=0x01;
digit3=0x06;
digit4=0x03;
}
}

