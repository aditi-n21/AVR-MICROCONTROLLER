#include <at89x52.h>
void display_digit(unsigned char);

#define dis_a P0_7
#define dis_b P2_7
#define dis_c P2_6
#define dis_d P2_4
#define dis_e P2_5
#define dis_f P0_6
#define dis_g P0_5

#define disp1 P2_3
#define disp2 P2_2
#define disp3 P2_1
#define disp4 P2_0

unsigned char count_val;
unsigned char digit1;
unsigned char digit2;
unsigned char digit3;
unsigned char digit4;

void timer_enable(void)
{
/*------------------------------------
Timer 0 routine for Display.
--------------------------------------*/
count_val=0x00;				/*Clear Count value*/
TMOD = (TMOD & 0x0F) | 0x20;  /* Set Mode (8-bit timer with reload) */
TH1 = 0x00;              /* Reload TL1 to count 100 clocks */
TL1 = 0xff;
ET1 = 1;                      /* Enable Timer 1 Interrupts */
TR1 = 1;                      /* Start Timer 1 Running */
EA = 1;                       /* Global Interrupt Enable */
/*--------------------------------------*/
}


void timer1_ISR (void) interrupt 3
{
disp1=0;
disp2=0;
disp3=0;
disp4=0;
if (count_val==1){
disp1=1;
disp2=0;
disp3=0;
disp4=0;
display_digit(digit1);
}
else if (count_val==2){
disp1=0;
disp2=1;
disp3=0;
disp4=0;
display_digit(digit2);
}
else if (count_val==0x03){
disp1=0;
disp2=0;
disp3=1;
disp4=0;
display_digit(digit3);
}
else if (count_val==0x04){
disp1=0;
disp2=0;
disp3=0;
disp4=1;
display_digit(digit4);
count_val=0x00;
}
count_val++;
}
/*---------------------------------------------------
Display the data passed to this function
----------------------------------------------------*/
void display_digit(unsigned char digg)
{
if (digg==0x00)
{
dis_a=0;
dis_b=0;
dis_c=0;
dis_d=0;
dis_e=0;
dis_f=0;
dis_g=1;
}
else if (digg==1)
{
dis_a=1;
dis_b=0;
dis_c=0;
dis_d=1;
dis_e=1;
dis_f=1;
dis_g=1;
}
else if (digg==2)
{
dis_a=0;
dis_b=0;
dis_c=1;
dis_d=0;
dis_e=0;
dis_f=1;
dis_g=0;
}
else if (digg==3)
{
dis_a=0;
dis_b=0;
dis_c=0;
dis_d=0;
dis_e=1;
dis_f=1;
dis_g=0;
}
else if (digg==4)
{
dis_a=1;
dis_b=0;
dis_c=0;
dis_d=1;
dis_e=1;
dis_f=0;
dis_g=0;
}
else if (digg==5)
{
dis_a=0;
dis_b=1;
dis_c=0;
dis_d=0;
dis_e=1;
dis_f=0;
dis_g=0;
}
else if (digg==6)
{
dis_a=0;
dis_b=1;
dis_c=0;
dis_d=0;
dis_e=0;
dis_f=0;
dis_g=0;
}
else if (digg==7)
{
dis_a=0;
dis_b=0;
dis_c=0;
dis_d=1;
dis_e=1;
dis_f=1;
dis_g=1;
}
else if (digg==8)
{
dis_a=0;
dis_b=0;
dis_c=0;
dis_d=0;
dis_e=0;
dis_f=0;
dis_g=0;
}
else if (digg==9)
{
dis_a=0;
dis_b=0;
dis_c=0;
dis_d=0;
dis_e=1;
dis_f=0;
dis_g=0;
}
else if (digg==0x0A)	/*For symbol -*/
{
dis_a=1;
dis_b=1;
dis_c=1;
dis_d=1;
dis_e=1;
dis_f=1;
dis_g=0;
}
}
