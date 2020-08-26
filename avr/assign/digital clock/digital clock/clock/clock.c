
#include <avr/io.h>
#include <util/delay.h>
void calldel(void);
void calldel()
{
	int i=0;
	
	for(i=0; i<2; i++)
	{
		
		PORTD|=(1<<PD4);
		_delay_ms(400);	               //_delay_ms(800)is the exact delay of 1 second to real time clock;
		PORTD&=~(1<<PD4);               //_delay_ms(800)=1sec;
		_delay_ms(400);
	}
}
int main(void)
{
	DDRC=0xff;
	DDRD|=(1<<PD0)|(1<<PD1);
	DDRD|=(1<<PD2)|(1<<PD3);
	DDRD|=(1<<PD4);   DDRB&=~(1<<PB3);
	PORTB|=(1<<PB3);
	unsigned char i,j,k,l,o,p,cnt;
unsigned char arr[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
	
while(1)
{
		for (i=0;i<3;i++)
	{
		if(i==2)
		{
			cnt=4;
		  }
		       else
		    {
			     cnt=10;
		      }
		         for (j=0;j<cnt;j++)
		       {
				   
			      for (k=0;k<6;k++)
			    {
				   for (l=0;l<10;l++)
				  
				 { 			PORTD=0xfe;
							PORTC=arr[i];
							_delay_ms(20);
							PORTD=0xfd;
							PORTC=arr[j];
							_delay_ms(20);
							PORTD&=~(1<<PD4);
							PORTD=0xfb;
							PORTC=arr[k];
							_delay_ms(20);
							PORTD=0xf7;
							PORTC=arr[l];
							_delay_ms(20);
							PORTD|=(1<<PD4);
							calldel();
						}
						
					}
				}
			}
		}
     }