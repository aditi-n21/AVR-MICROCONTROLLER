#include<reg51.h>

unsigned char name[25] = "Mrinal Embedded Solutions";
unsigned int i = 0;

void main()
{
    TMOD = 0x20;        // Timer 1 Mode 2
    TH1 = -3;           // Set the baudrate
    SCON = 0x50;        // Set serial mode 1; REN = 1
    TR1 = 1;            // Start Timer 1

	for(i = 0; i < 20000; i++);

    /*SBUF = 'M';
    while(TI == 0);
    TI = 0;*/

    while(1)
    {
        for(i = 0; i < 25; i++)
        {
            SBUF = name[i];
            while(TI == 0);
            TI = 0;
        }

        SBUF = 0x0A;		// Line Feed
        while(TI == 0);
        TI = 0;

        SBUF = 0x0D;		// Carriage Return
        while(TI == 0);
        TI = 0;
    }
}