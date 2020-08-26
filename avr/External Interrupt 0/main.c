#include<reg51.h>

 int i;
void Ext0ISR() 	interrupt 0
{	
    P0 =0x96;
	for(i=0; i<13000; i++);
    P0 =0x76;
		for(i=0; i<13000; i++);
    P0 =0x95;
		for(i=0; i<13000; i++);
    P0 =0x45;
		for(i=0; i<13000; i++);
    P0 =0x75;
		for(i=0; i<13000; i++);
    P0 =0x46;
		for(i=0; i<13000; i++);
    P0 =0x47;
		for(i=0; i<13000; i++);
    P0 =0x78;
		for(i=0; i<13000; i++);
    P0 =0x55;

}
				  
void Ext1ISR()	  interrupt 2
{
    P1 = ~P1;
}

void main()
{
   P0=0x00;
   P1=0x00;
    IT0 = 1;
    IT1 = 1;
	 IE = 0x85;
    while(1)
    {
	   
    }
}