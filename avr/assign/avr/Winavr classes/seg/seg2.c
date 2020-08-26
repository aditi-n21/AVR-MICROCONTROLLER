#include<avr/io.h>
#include<util/delay.h>

int main(void)
{
unsigned char arr[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90};
unsigned char i;
DDRB=0xff;
while(1)
{
for(i=0;i<10;i++)
{
  PORTB=~arr[i];
  _delay_ms(2000);

}
}
}