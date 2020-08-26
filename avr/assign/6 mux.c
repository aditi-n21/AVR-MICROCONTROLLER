/*
 * _6_mux.c
 *
 * Created: 8/24/2015 3:47:30 PM
 *  Author: DELL_PC
 */ 


#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRC=0xff;
	DDRD|=(1<<PD0)|(1<<PD1);
	DDRD|=(1<<PD2)|(1<<PD3);
	DDRD|=(1<<PD4)|(1<<PD5);
	unsigned char i,j,k,l,m,n,o,p,cnt;
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
			         {
						 for (m=0;m<6;m++)
						 {
							 for (n=0;n<10;n++)
							 {
				         PORTD=0xfe;
				         PORTC=arr[i];
				         _delay_us(100);
						 PORTD=0xfd;
						 PORTC=arr[j];
						 _delay_us(100);
						 PORTD=0xfb;
						 PORTC=arr[k];
						 _delay_us(100);
						 PORTD=0xf7;
						 PORTC=arr[l];
						 _delay_us(100);
						 PORTD=0xef;
						 PORTC=arr[m];
						 _delay_us(100);
						 PORTD=0xdf;
						 PORTC=arr[n];
						 _delay_us(100);
				         
			         }
					 
		         }
	         }
         }
} 
    }

}
	}