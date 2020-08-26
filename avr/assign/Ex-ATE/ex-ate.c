#include<reg51.h>
#include<string.h>

sbit led1=P1^0;
sbit led2=P1^1;
sbit led3=P1^2;
sbit sense1=P3^2;
sbit sense2=P3^3;
sbit mot1a=P3^7;
sbit mot1b=P3^6;
sbit mot2a=P3^5;
sbit mot2b=P3^4;


unsigned char recv(void);
//void trans(unsigned char);
//void transtr(unsigned char *);
void delay(unsigned int);

unsigned char cnt=0;
void main()
{
	unsigned char a;
	sense1=sense2=1;
	//IE=0x85;
	SCON=0x50;
	TMOD=0x20;
	TH1=-3;
	TR1=1;
	while(1)
	{		
	
		a=recv();
		switch(a)
		{
			case 'R': 
				         P2=0xfe;   //left
									break;
		//	case 'G':  
			//						P1=0xfd;   //up
				//					break;
			case 'Y': 
									P2=0xfd;     // down
									break;
			case 'S':   
									P2=0xf7;     // right
									if(cnt==0)
									{	
									led1=0;
										led2=1;led3=1;
									cnt++;
			            }
									else if(cnt==1)
									{
										led2=0;
										led1=1;led3=1;
										cnt++;
									}
									else
									{
										led3=0;led1=1;led2=1;
										cnt=0;
									}
									break;
			default:
				          P2=0xfb;
									break;
		}
	if(sense1==1)
	{		
		 mot1a=0;mot1b=1;mot2a=0;mot2b=1;
			   delay(20);
			 mot1a=0;mot1b=0;mot2a=0;mot2b=0;
		while((sense1==1)||(sense2==1));
		  
		mot1a=1;mot1b=0;mot2a=1;mot2b=0;
			   delay(20);
			 mot1a=0;mot1b=0;mot2a=0;mot2b=0;
		
	}
 if(sense2==1)
	{
		 mot1a=0;mot1b=1;mot2a=0;mot2b=1;
			   delay(20);
			 mot1a=0;mot1b=0;mot2a=0;mot2b=0;
    while((sense1==1)||(sense2==1));
			   mot1a=1;mot1b=0;mot2a=1;mot2b=0;
			   delay(20);
			 mot1a=0;mot1b=0;mot2a=0;mot2b=0;
	}

	}
}
/*unsigned char gate(void)
{
		if(sense1==0)
			  return 1;
    else if(sense2==0)
			  return 0;
		else 
			   return 2;
}*/
void delay(unsigned int msec)
{
	unsigned int i,j;
  for(i=0;i<msec;i++)
	  for(j=0;j<1275;j++);
}
/*void transtr(unsigned char *s)
{
unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
        {
          trans(*s);
					s++;
				}
}
void trans(unsigned char value)
{
	SBUF=value;
	while(TI==0);
	TI=0;
}*/
unsigned char recv(void)
{  unsigned char value;
   RI=0;
	while(RI==0);
	value=SBUF;
	return value;
}