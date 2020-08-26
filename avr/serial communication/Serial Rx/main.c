#include<reg51.h>

sbit q3 = P3^7;
sbit relay = P2^7;

unsigned char rec = 0;
unsigned int i = 0;

void main()
{
	for(i = 0; i < 20000; i++);
	for(i = 0; i < 20000; i++);
	for(i = 0; i < 20000; i++);

	q3 = 0;
	relay = 0;

    TMOD = 0x20;        // Timer 1 Mode 2
    TH1 = -3;           // Set the baudrate
    SCON = 0x50;        // Set serial mode 1; REN = 1
    TR1 = 1;            // Start Timer 1

	q3 = 1;

    while(1)
    {
        while(RI == 0);
        rec = SBUF;
        RI = 0;

        SBUF = rec + 1;
        while(TI == 0);
        TI = 0;

		if(rec == 0x31)
			relay = 1;
		else
			relay = 0;

		P0 = rec;
    }
}