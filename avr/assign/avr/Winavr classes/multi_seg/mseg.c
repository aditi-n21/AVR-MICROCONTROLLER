#include<avr/io.h>
#include<util/delay.h>
#define seg1 0
#define seg2 1
#define disp PORTB
int main(void)
{
unsigned char num[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char i,j;
DDRB=0xff;
DDRA=0xff;
PORTA&=~(1<<seg1);
PORTA&=~(1<<seg2);

while(1)
 {
  for(j=0;j<10;j++)
	{  
		for(i=0;i<10;i++)
		{
		 PORTA|=(1<<seg1);
		 disp=~num[i];
		 _delay_ms(70);
		 PORTA&=~(1<<seg1);
	     PORTA|=(1<<seg2); 
	     disp=~num[j];
         _delay_ms(100);
	      
		  PORTA&=~(1<<seg2);
		}
	}
 }
 return 0;
}
