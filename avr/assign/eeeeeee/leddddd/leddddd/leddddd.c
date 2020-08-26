#include <avr/io.h>
#include <util/delay.h>
unsigned int arr[]={0xcf88, 0x3f2a, 0xf300, 0x3f22, 0xf388, 0xc380, 0xa1e2, 0xcc88, 0x3322, 0x2322, 0xc094, 0x1022, 0xcc05, 0xcc11, 0xff00, 0xc788, 0x8f88, 0xc798, 0xbb88, 0x0322, 0xfc00, 0x0005, 0xcc50, 0x0055, 0x0023, 0x3344};
int main(void)
{
	int count=0;
	DDRA=DDRB=0xff;
    while(1)
    {
		int j,k;
		for(j=0; j<26; j++)
		{
		count=count%26;
		PORTB=arr[count];
		PORTA=arr[count]>>8;
		_delay_ms(1000);
		count=count+1;
		}
		for(k=0; k<26; k++)		
       {
		   count=count/1;
		   PORTB=arr[count];
		   PORTA=arr[count]>>8;
		   _delay_ms(1000);
		   count=count-1;
	   }
    }
}