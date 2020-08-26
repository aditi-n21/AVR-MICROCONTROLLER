#include<reg51.h>
#define led P1 
void main()
{
unsigned char i;
	while(1)
	{
for(i=0;i<255;i++)
  led=i;

}


}