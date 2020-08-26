#include<reg51.h>
#include<string.h>

#define lcd P1
#define seg P0
sbit buzz=P2^5;
sbit ledf=P2^6;
sbit ledb=P2^7;
sbit emsw=P3^2;   // emergency sw


sbit en=P3^3;
sbit rs=P3^5;
sbit rw=P3^4;

sbit sense=P2^4;   // entry check
sbit sw=P3^6;			// exit
sbit rotor_a = P2^0;
sbit rotor_b = P2^1;
sbit rotor_c = P2^2;
sbit rotor_d = P2^3;

sbit enter=P3^0;   //inc
sbit sw1=P3^1;     

void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void delay(unsigned char);
void lcd_str(unsigned char *s);
void stepperf(unsigned char);
void stepperb(unsigned char);

unsigned char num[]={0xc0,0x0f9,0x0a4,0x0b0,0x99,0x92,0x82,0x0f8,0x80,0x90};
unsigned char cnt,time,count=0;

void external0(void) interrupt 0
{
buzz=0;
delay(50);
	buzz=1;
}
void timer0(void) interrupt 1
{
  
time--;
//	TF0=0;
}

void lcd_cmd(unsigned char z)
{
lcd=z;
rs=0;
rw=0;
en=1;
delay(5);
en=0;
}
void lcd_data(unsigned char z)
{
lcd=z;
rs=1;
rw=0;
en=1;
delay(5);
en=0;
}
void lcd_init(void)
{
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x0e);
lcd_cmd(0x06);
lcd_cmd(0x80);
}

void lcd_str(unsigned char *s)
{
unsigned l,i;
l=strlen(s);
for(i=0;i<l;i++)
{
lcd_data(*s);
s++;
}
}
void delay(unsigned char t)
{
unsigned int i,j;
for(i=0;i<t;i++)
for(j=0;j<1275;j++);
}
void stepperf(unsigned char msec)
{
	unsigned int i;
	for(i=0;i<msec;i++)
		{
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
		}
}
void stepperb(unsigned char msec)
{
	unsigned int i;
	for(i=0;i<msec;i++)
		{
			rotor_a=0;
rotor_b=0;
rotor_c=0;
rotor_d=1;
			delay(10);
			rotor_a=0;
rotor_b=0;
rotor_c=1;
rotor_d=0;
			delay(10);
			rotor_a=0;
rotor_b=1;
rotor_c=0;
rotor_d=0;
			delay(10);
			rotor_a=1;
rotor_b=0;
rotor_c=0;
rotor_d=0;
			delay(10);
		}
}
void main()
{
unsigned char arr[10],x,y;
lcd_init();
IE=0x83;
TMOD=0x02;
TH0=0xd2;
IP=0x01;
ledf=1;
ledb=1;
buzz=1;
emsw=1;
sw=1;
sw1=1;
enter=1;
time=255;
seg=num[cnt];
lcd_cmd(0x01);
lcd_str("WELCOME TO ALL");
while(1)
{	ledf=0;
     ledb=1;
	 lcd_cmd(0x01);
    lcd_cmd(0x80);
  	lcd_str("STATION CODES:-");
    lcd_cmd(0xc0);
		lcd_str("RKSH-01  HW-02 ");
			delay(50);
		lcd_cmd(0x01);
    lcd_cmd(0x80);
  	lcd_str("COER-03 RK-04 ");
    lcd_cmd(0xc0);
		lcd_str("SRE-05");
		delay(50);
		lcd_cmd(0x01);
    lcd_cmd(0x80);
  	lcd_str("CURRENT STATION");
    lcd_cmd(0xc0);
		lcd_str("Rishikesh");
		while(time>0)
		{
			TR0=1;
			x=time/10;
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
			lcd_data(y+48);
			if(sense==0)
				{  
					if(cnt<9)
						cnt++;
					else
					{
		   			lcd_cmd(0x01);
					lcd_cmd(0x80);
					lcd_str("FULL");
					buzz=0;
					}
				//seg=num[cnt];
					lcd_cmd(0x01);
	  				lcd_cmd(0x82);
					lcd_str("Enter Station code");
					lcd_cmd(0xc0);
	  				lcd_str("Press key :-");
			
					while(sw1==1)
					{
					if(enter==0)
						{
						if(count<5)
						{	
							count++;
							x=count/10;
							y=count%10;
							lcd_cmd(0xce);
							lcd_data(x+48);
							lcd_data(y+48);
							delay(50);
							
						}
						else
						{
							count=0;

						}
						}
					  
					}
						lcd_cmd(0x01);
						lcd_cmd(0x80);
  	lcd_str("CURRENT STATION");
    lcd_cmd(0xc0);
		lcd_str("Rishikesh");
				}
			if(sw==0)
				{
					if(cnt>0)
						cnt--;
		 /*else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
				}
			seg=num[cnt];	
	// delay(100);
	 
			}
			arr[cnt]=count;
			count=0;
			TR0=0;
			time=255;
			buzz=0;
			delay(10);
			buzz=1;
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("NEXT STATION");
			lcd_cmd(0xc0);
			lcd_str("Haridwar");
			stepperf(20);
//	delay(10);
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			lcd_str("CURRENT STATION");
			lcd_cmd(0xc0);
			lcd_str("Haridwar");
			while(time>0)
			{
				TR0=1;
				x=time/10;
				y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
			lcd_data(y+48);
			if(sense==0)
				{  
					if(cnt<9)
						cnt++;
				else
					{
						lcd_cmd(0x01);
						lcd_cmd(0x80);
						lcd_str("FULL");
						buzz=0;
					}
			   lcd_cmd(0x01);
			   lcd_cmd(0x82);
	   		   lcd_str("Enter Station code");
			   lcd_cmd(0xc0);
			   lcd_str("Press key :-");
			 
		    	while(sw1==1)
				{
				if(enter==0)
					{
					if(count<5)
					{
						count++;
						x=count/10;
						y=count%10;
						lcd_cmd(0xce);
						lcd_data(x+48);
						lcd_data(y+48);
						delay(50);
							
					}
					else
					{
						count=0;
					}
					}
				  
				}
				lcd_cmd(0x01);
					lcd_cmd(0x80);
			lcd_str("CURRENT STATION");
			lcd_cmd(0xc0);
			lcd_str("Haridwar");
				 //seg=num[cnt];
				}
				if(sw==0)
					{	 
						if(cnt>0)
							cnt--;
		 /*else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
					}
				seg=num[cnt];
		
			// delay(10);
			}
			arr[cnt]=count;
			count=0;
				TR0=0;
				time=255;
				buzz=0;
				delay(10);
				buzz=1;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
				stepperf(19);
			//delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
				while(time>0)
					{
						TR0=1;
					x=time/10;
		
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
				lcd_data(y+48);

						if(sense==0)
							{  
								if(cnt<9)
									cnt++;
								else
								{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
								}
									lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
	  
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
					
			}
			else
			{
			count=0;
			}
			}
	}
	lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
							//seg=num[cnt];
						}
					if(sw==0)
						{	
							if(cnt>0)
							cnt--;
		 /*else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
						}
						seg=num[cnt];
		
	// delay(10);
				}
			arr[cnt]=count;
			count=0;
				TR0=0;
				time=255;
				buzz=0;
				delay(10);
				buzz=1;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
				stepperf(7);
			//delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
				while(time>0)
					{
						TR0=1;
					x=time/10;
		
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
				lcd_data(y+48);

						if(sense==0)
							{  
								if(cnt<9)
									cnt++;
								else
								{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
								}
									lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
	 
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
					
			}
			else
			{
			count=0;
			}
			}
		
}
		   lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
							//seg=num[cnt];
						}
					if(sw==0)
						{	
							if(cnt>0)
							cnt--;
		 /*else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
						}
						seg=num[cnt];
		
	// delay(10);
				}
			arr[cnt]=count;
			count=0;
				TR0=0;
				time=255;
				buzz=0;
				delay(10);
				buzz=1;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("Saharanpur");
				stepperf(36);
			//delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Saharanpur");
				while(time>0)
					{
						TR0=1;
					x=time/10;
					y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
					lcd_data(y+48);
						if(sense==0)
							{  
								if(cnt<9)
									cnt++;
								else
								{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
								}
									lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
					
			}
			else
			{
			count=0;
			}
			}
		 }
 	lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Saharanpur");
				//seg=num[cnt];
						}
					if(sw==0)
						{	
							if(cnt>0)
							cnt--;
		 /*else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
						}
						seg=num[cnt];
			 
	// delay(10);
				}
				arr[cnt]=count;
				count=0;
				TR0=0;
				time=255;	
				buzz=0;
				delay(10);
				buzz=1;
				ledf=1;
				ledb=0;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
				stepperb(36);
	//	delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
				while(time>0)
					{
						TR0=1;
						x=time/10;
		
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
				lcd_data(y+48);
						if(sense==0)
						{  
							if(cnt<9)
								cnt++;
							else
							{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
				 //delay(10);
							}	lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
						
			}
			else
			{
			count=0;
			}
			}
	
  }
  lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Roorkee");
			 //seg=num[cnt];
						}
					if(sw==0)
					{	
						if(cnt>0)
							cnt--;
		/* else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
					}
					seg=num[cnt];
		
	// delay(10);
			}
			
				arr[cnt]=count;
				count=0;
				TR0=0;
				time=255;	
				buzz=0;
				delay(10);
				buzz=1;
				ledf=1;
				ledb=0;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
				stepperb(7);
	//	delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
				while(time>0)
					{
						TR0=1;
					x=time/10;
		
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
			
			lcd_data(y+48);

						if(sense==0)
						{  
							if(cnt<9)
								cnt++;
							else
							{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
				 //delay(10);
							}	lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
					
			}
			else
			{
			count=0;
			}
			}
    		}
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("COER");
		 //seg=num[cnt];
						}
					if(sw==0)
					{	
						if(cnt>0)
							cnt--;
		/* else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
					}
					seg=num[cnt];
		
	// delay(10);
			}
				arr[cnt]=count;
				count=0;
				TR0=0;
				time=255;	
				buzz=0;
				delay(10);
				buzz=1;
				ledf=1;
				ledb=0;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("Haridwar");
				stepperb(19);
	//	delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Haridwar");
				while(time>0)
					{
						TR0=1;
						x=time/10;
		
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
					lcd_data(y+48);
						if(sense==0)
						{  
							if(cnt<9)
								cnt++;
							else
							{
								lcd_cmd(0x01);
								lcd_cmd(0x80);
								lcd_str("FULL");
								buzz=0;
				 //delay(10);
							}	lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
					delay(50);
					
			}
			else
			{
			count=0;
			}
			}
		
}
	lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Haridwar");
	//seg=num[cnt];
						}
					if(sw==0)
					{	
						if(cnt>0)
							cnt--;
		/* else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
					}
					seg=num[cnt];
		
	// delay(10);
			}
			arr[cnt]=count;
			count=0;
				TR0=0;
				time=255;
				buzz=0;
				delay(10);
				buzz=1;
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("NEXT STATION");
				lcd_cmd(0xc0);
				lcd_str("Rishikesh");
				stepperb(20);
	//delay(10);
				lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Rishikesh");
				while(time>0)
				{
					TR0=1;
					x=time/10;
			
			y=time%10;
			lcd_cmd(0xcb);
			lcd_data(x+48);
					lcd_data(y+48);

					if(sense==0)
					{  
						if(cnt<9)
						cnt++;
						else
						{
							lcd_cmd(0x01);
							lcd_cmd(0x80);
							lcd_str("FULL");
							buzz=0;
							delay(10);
						}
							lcd_cmd(0x01);
	  lcd_cmd(0x82);
	  lcd_str("Enter Station code");
		lcd_cmd(0xc0);
	  lcd_str("Press key :-");
			while(sw1==1)
		{
			if(enter==0)
			{
			if(count<5)
			{	count++;
					x=count/10;
	y=count%10;
	lcd_cmd(0xce);
	lcd_data(x+48);
  lcd_data(y+48);
				delay(50);
			
			}
			else
			{
			count=0;
			}
		  	}   
	}
		lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_str("CURRENT STATION");
				lcd_cmd(0xc0);
				lcd_str("Rishikesh");
		 //seg=num[cnt];
					}
				if(sw==0)
						{	
							if(cnt>0)
							cnt--;
/*		 else
		 {
		  lcd_cmd(0x01);
     lcd_cmd(0x80);
  	lcd_str("EMPTY");
		 }*/
						}
					seg=num[cnt];
			
	 delay(2);
				}
				arr[cnt]=count;
				count=0;
					TR0=0;
					time=255;
//	lcd_cmd(0x01);
				lcd_cmd(0x80);
				lcd_cmd(0x01);	
				lcd_str("TRAIN STOPS HERE");
				lcd_cmd(0xc0); 
				lcd_str("  THANK YOU");
				cnt=0;
		}
}	