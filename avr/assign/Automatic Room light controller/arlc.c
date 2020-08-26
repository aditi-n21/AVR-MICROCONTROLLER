#include<reg51.h>
#include<string.h>
#define LCD P1 

sbit RS=P3^7; 
sbit RW=P3^6;
sbit EN=P3^5;
sbit sense1=P3^0;
sbit sense2=P3^1;
sbit relay1=P3^2;
sbit relay2=P3^3;
 
void lcd_cmd(unsigned char);
void lcd_data(unsigned char);
void lcd_init(void);
void lcd_str(unsigned char *);
void delay_ms(unsigned int);

 unsigned int cnt=0; 
void main(void)
{
 sense1=sense2=1;

    lcd_init();
	 lcd_cmd(0x80);
		   lcd_str("AUTOMATIC ROOM");
		    lcd_cmd(0xc0);
		   lcd_str("LIGHT CONTROLLER");
		   delay_ms(500);
		    lcd_cmd(0x01);
		   lcd_str("MADE BY:-");
		    lcd_cmd(0xc0);
		   lcd_str("Vipul Sharma");
		    delay_ms(500);	
			   lcd_cmd(0x01);
		    
    while(1)
{   
	
		   	lcd_cmd(0x80);
		   lcd_str("No.of persons");
		   lcd_cmd(0x8e);
		   lcd_data(cnt+48);
		    delay_ms(20);  
   if(sense1==1)
          { 
           cnt++;
		   delay_ms(20);
           lcd_cmd(0x80);
		   lcd_str("Entry Detected ");
		  delay_ms(100); 
          lcd_cmd(0x01);
			 if(cnt<=0)
             {
			 break;
			  
			  }
			  else
			  {
			  lcd_cmd(0xc0);
               lcd_str("LIGHTS ON ");
			   // delay_ms(20);
			   	relay1=0;
			  relay2=0;
			  // delay_ms(200);
			 
			  }
		    } 
  
  if(sense2==1)
          { 
          
		 //  delay_ms(500); 
		lcd_cmd(0x01);
		 if(cnt<=1)
            {
			 lcd_cmd(0xc0);
               lcd_str("LIGHTS OFF");
				    cnt=0;
		   		  relay1=1;
				  	  relay2=1;
		 } 
		 else
		 {
		    cnt--;
		 
           lcd_cmd(0x80);
		   lcd_str("Exit Detected ");
		     delay_ms(100);
		 	lcd_cmd(0x01);
		 }
          } 
	  		
	 	       
            
        }
           
}

void delay_ms(unsigned int i)
{
unsigned int j;
            while(i-->0)
            {
                        for(j=0;j<500;j++)
                        {
                                    ;
                        }
            }
}           


void lcd_init() 
{
lcd_cmd(0x38);
lcd_cmd(0x01);
lcd_cmd(0x06);
lcd_cmd(0x0E);
lcd_cmd(0x80);
}
void lcd_cmd(unsigned char value) 
{
LCD=value;
RS=0;
RW=0;
EN=1;
delay_ms(2);
EN=0;
}
void lcd_data(unsigned char value) 
{
LCD=value;
RS=1;
RW=0;
EN=1;
delay_ms(2);
EN=0;
}

void lcd_str(unsigned char *s)
{
/*	unsigned char l,j;
	l=strlen(s);
	//for(j=0;j<l;j++)
		while(*s!='\0')
		{
			lcd_data(*s);
			s++;
		//	delay(100);
		}*/
while(*s)
lcd_data(*s++);
} 
