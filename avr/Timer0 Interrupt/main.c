#include<reg51.h>

char i = 0;

void T0_ISR() interrupt 1
{
    P3 = ~P3;           // toggle @ of 50 msec

    if(i > 19)  
    {
        P0 = ~P0;       // toogle @ of 1 sec
        i = 0;
   	}

    i++;

    TF0 = 0;
}

void T0Init()
{
    TMOD = 0x01;    // Timer 0 Mode 1
    TH0 = 0x4B;
    TL0 = 0xFD;
    TR0 = 1;
    IE = 0x82;
}

void main()
{
    P0 = 0x00;
    P1 = 0x00;
    P3 = 0x00;

    T0Init();
    
    while(1)
    {
        P1 = ~P1;       // toogle vey fast
    }   
}