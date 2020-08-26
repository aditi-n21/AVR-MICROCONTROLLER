#include<reg52.h>
//---------------------------------Defining Macros-------------
                                                                                                                                                                         
//

sbit RS=P3^7;
sbit EN=P3^6;
sbit RLY1=P1^0;

unsigned char pulse=0;

void timer0() interrupt 0
{
 	pulse++;
}

#define TIMEOUT 20000
#define NO_OF_RETRY 5

//---------------------------------------
// Forward function declaration
//---------------------------------------
void send_cmd(unsigned char *cmd);
void Txmsg(unsigned char *no,unsigned char *msg,unsigned char a1);
unsigned char Rxmsg(void);
void lcdinit(void);
void lcdclear(void);
void lcdData(unsigned char l);
void lcdcmd(unsigned char k);
void DelayMs(unsigned int count);
void InitModem(void);
void lcd_puts(unsigned char *p);
void uart_puts(unsigned char *p);
void uart_gets(unsigned char *p,unsigned char len);
void uart_putchar(unsigned char p);
void uart_getchar(unsigned char *p);

void wait();
void acknowledge();
void signal_strength(void);

unsigned char status=0,ret=0,mno[]="+917417584592";

//---------------------------------------
// Main rotine
//---------------------------------------
void main()
{
TMOD=0x40;			                        // Configure UART at 9600 baud rate
TH1=0xFa;
SCON=0x50;

TR1=1;

EA=1;
EX0=1;
IT0=0;

RLY1=0;

lcdinit();			                        // Initialize LCD
lcd_puts("INITIALIZING     MODEM...PLZ WAIT");
DelayMs(10000);
InitModem();		// Initialize Modem

//Txmsg(mno,"GSM BASED ENERGY METER WITH TEMPER PROOF",pulse);
//DelayMs(1000);
EA=1;
while(1)
{  
ret=Rxmsg();
if(ret==1)
Txmsg(mno,"POWER ON, METER READING=",pulse);
if(ret==2)
Txmsg(mno,"POWER OFF, METER READING=",pulse);
if(ret==3)
Txmsg(mno,"CURRENT REDING OF METER=",pulse);
																 
}
}

//----------------------------------------------------
// send command subroutine to check the connectivity of modem
//----------------------------------------------------
void send_cmd(unsigned char *cmd)
{
unsigned char i,buff[6];
retry:
lcdclear();
uart_puts(cmd);		     // Sending Command
uart_putchar(0x0d);      // Enter
uart_gets(buff,6);		 // Receive response
DelayMs(100);

for(i=0;i<6;i++)	     // Compare response
{
if(buff[i]=='a' ||  buff[i]=='b')
goto retry;
if(buff[i]=='e' ||  buff[i]=='j')
return;
}
}

//---------------------------------------
// Modem initialization subroutine
//---------------------------------------

void Txmsg(unsigned char *no, unsigned char *msg,unsigned char a1)
{
unsigned char i=0,j=0,buff[20],d1,d2,d3;

retry:
j++;
send_cmd("at");					  // AT command sending to check the connectivity
lcdclear();
uart_puts("at+cmgs=\"");
lcdcmd(0xC0);
uart_puts(no);
DelayMs(100);
uart_putchar('"');
uart_putchar(0x0d); 
lcdclear();
uart_getchar(buff);
uart_puts(msg);
while(a1!=0)
{
d1=a1%10;
d1+=0x30;
	//digits before desible point
a1=a1/10;
d2=a1%10;
d2+=0x30;

a1=a1/10;
d3=a1%10;
d3+=0x30;

a1=a1/10;
}
uart_putchar(d3);
uart_putchar(d2);
uart_putchar(d1);
uart_putchar(26);
lcdclear();
uart_gets(buff,20);
DelayMs(1000);

for(i=0;i<10;i++)			     //command to recv data
{
if(buff[i]=='+' && buff[i+1]=='C' && buff[i+2]=='M' && buff[i+3]=='G')
return;
}
if(j<NO_OF_RETRY)

} 

//---------------------------------------
// Recieve message subroutine
//---------------------------------------
unsigned char Rxmsg(void)
{
unsigned char i=0,ret=0;
unsigned int j=0;
unsigned char c[84];	

retry: 
if(push==1)
{
	return 4;
}
send_cmd("at");					  // AT command sending to check the connectivity
DelayMs(100);
lcdclear();
uart_puts("at+cmgr=1");
DelayMs(100);
uart_putchar(0x0d); 

lcdcmd(0xC0);
EA=0;
for(i=0;i<84;i++)
{
j=0;
while(RI==0)
{
if(j>=TIMEOUT)
goto timeout;
wait();
j++;
}
c[i]=SBUF;
RI=0;
lcdData(c[i]);
}
//EA=1;
DelayMs(1000);

timeout:
for(i=0;i<5;i++)			  //command to recv data
{
if((c[i]=='O') || (c[i]=='K'))
return ret;
}


goto retry;

sucess1:
i=i+7;

for(j=0;j<13;j++)
{
mno[j]=c[i];
i++;
DelayMs(10);
}
mno[j]='\0';

for(;i<84;i++)
{
if((c[i]=='3') && (c[i+1]=='5') && (c[i+2]=='7') && (c[i+3]=='9') && (c[i+4]=='1'))
goto sucess;
}
goto delete;

sucess:
for(i=0;i<84;i++)
{
if((c[i]=='O') && (c[i+1]=='N'))
{
RLY1=1;
ret=1;
}

if((c[i]=='O') && (c[i+1]=='F') && (c[i+2]=='F'))
{
RLY1=0;
ret=2;
}
if((c[i]=='R') && (c[i+1]=='E') && (c[i+2]=='A') && (c[i+3]=='D'))
{
ret=3;
}
}
delete:
send_cmd("at+cmgd=1");			  // sending AT+CMGD to delete message 
return ret;
}

//---------------------------------------
// Lcd initialization subroutine
//---------------------------------------
void lcdinit(void)
{
lcdcmd(0x38);
DelayMs(250);
lcdcmd(0x0E);
DelayMs(250);
lcdcmd(0x01);
DelayMs(250);
lcdcmd(0x06);
DelayMs(250);
lcdcmd(0x80);
DelayMs(250);
}

//---------------------------------------
// Lcd initialization subroutine
//---------------------------------------
void lcdclear(void)
{
lcdcmd(0x01);
DelayMs(1);
lcdcmd(0x80);
DelayMs(1);
}

//---------------------------------------
// Lcd data display
//---------------------------------------
void lcdData(unsigned char l)
{
P2=l;
RS=1;
EN=1;
DelayMs(1);
EN=0;
}

//---------------------------------------
// Lcd command
//---------------------------------------
void lcdcmd(unsigned char k)
{
P2=k;
RS=0;
EN=1;
DelayMs(1);
EN=0;
}			   

//---------------------------------------
// Delay mS function
//---------------------------------------
void DelayMs(unsigned int count) 
{											// mSec Delay 11.0592 Mhz 
    unsigned int i;		      				// Keil v7.5a 
    while(count) {
        i = 115; 			 				// 115	exact value
		while(i>0) i--;
        count--;
    }
}

//---------------------------------------------------------------------------------------------------------------------------
//--------------------------a small delay fxn to ensure the line settels down after transition-------------------------------

 void wait()
 {
    char i;
    for(i=0;i<=10;i++)
		i++;
    return;
 }

void lcd_puts(unsigned char *p)
{
unsigned char i=0;

while(p[i]!='\0')
{
lcdData(p[i]);
if(i==16)
lcdcmd(0xC0);
i++;
}
}

void uart_puts(unsigned char *p)
{
while(*p!='\0')
{
lcdData(*p);
uart_putchar(*p);
DelayMs(10);
p++;
}
}

void uart_putchar(unsigned char p)
{
SBUF=p;
while(TI==0);
TI=0;
}

void uart_gets(unsigned char *p,unsigned char len)
{
unsigned int i,j;

for(i=0;i<len;i++)			  //command to recv data
{
j=0;
while(RI==0)
{
if(j>=TIMEOUT)
break;
wait();
j++;
}
p[i]=SBUF;
RI=0;
lcdData(p[i]);
}
}

void uart_getchar(unsigned char *p)
{
unsigned int i,j;

i=0;
do
{
j=0;
while(RI==0)
{
if(j>=TIMEOUT)
break;
wait();
j++;
}
p[i]=SBUF;
RI=0;
lcdData(p[i]);
i++;
} while(p[i]!='>' && i<5);
}

void signal_strength(void)
{
unsigned char i,buff[12];
retry:
lcdclear();
uart_puts("at+csq");	 // Sending Command
uart_putchar(0x0d);      // Enter
lcdcmd(0xC0);
uart_gets(buff,12);		 // Receive response
DelayMs(1000);

for(i=0;i<12;i++)	     // Compare response
{
if(buff[i]=='E' ||  buff[i]=='R')
goto retry;
if(buff[i]=='+' &&  buff[i+1]=='C')
{
if(buff[i+6]>'3')
goto retry;
else
{
lcdclear();
lcd_puts("Signal Strength");
lcdcmd(0xC0);
lcdData(buff[i+6]);
lcdData(buff[i+7]);
DelayMs(1000);
return;
}
}
}
goto retry;
}