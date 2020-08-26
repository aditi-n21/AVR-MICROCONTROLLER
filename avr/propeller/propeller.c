  #include<reg51.h> 
                                                                                                                           
#define led P1                      //port01 will be connected to leds 

void display(unsigned char car);
                                                              
unsigned int del=50,k;    //variable to control 
unsigned char msg[]="PROPELLER DISPLAY";

void external0(void) interrupt 0
{
 TR0=0;
 k=0;
 TH0=0xf9;
 TL0=0x69;
 TR0=1;

}
  void timer0(void) interrupt 1
{
k++;
  display(msg[k]);
 TF0=0;
}                                                                                         
void delay(void)
{
 unsigned int i,j;
	for(i=0;i<del;i++)
		for(j=0;j<1275;j++);
}
void display(unsigned char cart)
{
   switch(cart)
  {
  	case 'A' : 
   	 {
    led=0x81;  delay( ); 
    led=0x6f;  delay( );  
	led=0x6f;  delay( ); 
	led=0x81;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
   case 'P' : 
   
   {
    led=0x01;  delay( ); 
    led=0xED;  delay( );  
	led=0xED;  delay( ); 
	led=0xF3;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
   case 'R' : 
    {
    led=0x01;  delay( ); 
    led=0xED;  delay( );  
	led=0xED;  delay( ); 
	led=0x13;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
	case 'O':
     {
    led=0x83;  delay( ); 
    led=0x7D;  delay( );  
	led=0x7D;  delay( ); 
	led=0x83;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
	case 'E' :
     {
    led=0x01;  delay( ); 
    led=0x6D;  delay( );  
	led=0x7D;  delay( ); 
	led=0x7D;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
	case 'L' : 
   
   {
    led=0x01;  delay( ); 
    led=0x7f;  delay( );  
	led=0x7f;  delay( ); 
	led=0x7F;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;case 'D' : // letter A
   
   {
    led=0x01;  delay( ); 
    led=0x7D;  delay( );  
	led=0xBB;  delay( ); 
	led=0xC7;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;case 'I' : // letter A
   
   {
    led=0x7D;  delay( ); 
    led=0x7D;  delay( );  
	led=0x01;  delay( ); 
	led=0x7D;  delay( );
	led=0x7D;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
	case 'S':
   	{
    led=0x73;  delay( ); 
    led=0x6D;  delay( );  
	led=0x5D;  delay( ); 
	led=0x9D;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
	case 'Y' : // letter A
    {
    led=0xF1;  delay( ); 
    led=0xEf;  delay( );  
	led=0x1f;  delay( ); 
	led=0xEf;  delay( );  
	led=0xF1;  delay( ); 
	led=0xff;  delay( );// to make one column gap between letters  
   } 
    break;
   case ' ' : // space
   
   {
    led=0xff;  delay( );
	led=0xff;  delay( ); 
	led=0xff;  delay( );  
	led=0xff;  delay( ); 
	led=0xff;  delay( ); 
	led=0xff;  delay( ); 
    led=0xff;  delay( );// to make one column gap between letters 
  
   } break;

  default:
   led=0xfF;
   break;
}
}

void main()
{

TMOD=0x01;
IE=0x83;
IP=0x01;
IT0=1;
TH1=0xf9;
TH1=0x69;
led=0xff;

TR0=1;
while(1)
{
  for(k=0;k<18;k++)
{
  led=msg[k];
 
}

}
}
