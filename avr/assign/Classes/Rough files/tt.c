 #include<reg51.h>
#include<string.h>
#define LCD P0
sbit rs=P0^0;
sbit rw=P0^1;
sbit en=P0^2;
sbit row1=P3^0;
sbit row2=P3^1;
sbit row3=P3^2;
sbit col1=P3^5;
sbit col2=P3^6;
sbit col3=P3^7;
sbit led1=P2^0;
sbit led2=P2^1;
sbit led3=P2^2;
sbit led4=P2^3;
sbit led5=P2^4;
sbit led6=P2^5;

void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void delay(unsigned char);
unsigned char keysense(void);
void player2(void);
void player1(void);
void selctmode(void);
/*void timer0(void) interrupt 1
{
	led4=~led4;
	led5=~led5;
	led6=~led6;
	//  delay(10);
}*/
unsigned char keysense(void)
{
	while(1)
	{
		col1=0;
		col2=1;
		col3=1;
		if(row1==0)	
			return(1);
		if(row2==0)
			return(4);
		if(row3==0)
			return(7);
		col1=1;
		col2=0;
		col3=1;
		if(row1==0)
			return(2);
		if(row2==0)
			return(5);
		if(row3==0)
			return(8);
		col1=1;
		col2=1;
		col3=0;
		if(row1==0)
			return(3);
		if(row2==0)
			return(6);
		if(row3==0)
			return(9);
	};
}	 

void lcd_str(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		lcd_data1(*s);
		s++;
	}
}

void lcd_init(void)
{
	lcd_cmd1(0x02);
	delay(5);
	lcd_cmd1(0x28);
	delay(5);
	lcd_cmd1(0x01);
	delay(5);
	lcd_cmd1(0x0e);
	delay(5);
	lcd_cmd1(0x06);
	delay(5);
	lcd_cmd1(0x82);
	delay(5);
}	
void lcd_cmd(unsigned char value)
{
	LCD=value;
	rs=0;
	rw=0;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_cmd1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_cmd(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_cmd(cd1);
}	
void delay(unsigned char itime)
{
unsigned char i;
unsigned int j;
for(i=0;i<itime;i++)
for(j=0;j<1275;j++);

}
void lcd_data(unsigned char value)
{
	LCD=value;
	rs=1;
	rw=0;
	en=1;
	delay(5);
	en=0;
	delay(5);
}
void lcd_data1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_data(cd1);
}	
void selctmode(void)
{
     unsigned char k;
	aa: lcd_cmd1(0x80);
	 lcd_str("Select Ur mode");
	 lcd_cmd1(0xc0);
		lcd_str("1. 1P 2. 2P");
		k=keysense();
		if(k==1)
		  {
		    lcd_cmd1(0x01);
		lcd_str("1 Player Mode");
		  player1();
		  }
		  else if(k==2)
		  {
		  	    lcd_cmd1(0x01);
		lcd_str("2 Player Mode");
		 player2();
		  }
		else
		   {
		     lcd_cmd1(0x01);
		lcd_str("wrong selection");
		goto aa;
		
		   }
		   
}
void player2(void)
{	unsigned char k;
     
	 led1=led2=led3=1;
	 led4=led5=led6=0;
	  
	   TR0=0;
	  lcd_cmd1(0x01);
	  lcd_str("Player 1 turn");
	 
	  k=keysense();
	  led4=led5=led6=1;	 
	
	    
		
	 switch(k)
	{
   	case 1: led1=1;led2=0;led3=0;led4=0;led5=1;led6=1;
	        break;
	case 2: led1=1;led2=0;led3=0;led5=0;led4=1;led6=1;
	        break;
    case 3: led1=1;led2=0;led3=0;led6=0;led5=1;led4=1;
	        break;
	case 4: led2=1;led1=0;led3=0;led4=0;led5=1;led6=1;
			break;
	case 5: led2=1;led1=0;led3=0;led5=0;led4=1;led6=1;
			break;
	case 6: led2=1;led1=0;led3=0;led6=0;led5=1;led4=1;
			break;
	case 7: led3=1;led1=0;led2=0;led4=0;led5=1;led6=1;
			break;
	case 8: led3=1;led5=0;led1=0;led2=0;led4=1;led6=1;
			break;
	case 9: led3=1;led6=0;led1=0;led2=0;led5=1;led4=1;
			break;
	default:
			break;

	}
   lcd_cmd1(0x01);
	  lcd_str("Player 2 turn");
	  
}
void main()
{
	unsigned char a;
	//IE=0x82;
	//TMOD=0x02;
	//TH0=0xd2;
	P3=0x07;
	//char arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	 	lcd_init();
	  	lcd_str("WELCOME To");
		lcd_cmd1(0xc0);
		lcd_str("TIC TAC TOE");
		lcd_cmd1(0x01);
	while(1)
	{ selctmode();
	a=keysense();
	switch(a)
	{
   case 0: 
			break;
	case 1: 
	        break;
	case 2: 
	        break;
    case 3: 
	        break;
	case 4: 
			break;
	case 5: 
			break;
	case 6: 
			break;
	case 7: 
			break;
	case 8: 
			break;
	case 9: 
			break;
	default:
			break;

	}
 }

}


