 #include<reg51.h>
 #define led P2
 void delay(unsigned char);
 void main()
 {
 while(1)
 {
 led=0x33;
 delay(50);
 led=0xcc;
 delay(50);

 
 }
 
 
 }
 void delay(unsigned char itime)
 {
 unsigned char i;
 unsigned int j;
 for(i=0;i<itime;i++)
 for(j=0;j<1275;j++);
 

 
 }