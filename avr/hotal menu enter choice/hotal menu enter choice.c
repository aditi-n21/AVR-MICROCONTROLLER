/*
 * hotal_menu_enter_choice.c
 *
 * Created: 9/10/2015 8:09:22 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
#include <util/delay.h>
#define data PORTD
#define control PORTD
#define rs PD0
#define rw PD1
#define en PD2
#define row1 PB3
#define row2 PB4
#define row3 PB5
#define row4 PB6
#define col1 PB0
#define col2 PB1
#define col3 PB2
#define keyin PINB
#define key PORTB

void lcd_init(void)
{
	cmndbrk(0x02);
	cmndbrk(0x28);
	cmndbrk(0x01);
	cmndbrk(0x06);
	cmndbrk(0x0e);
	cmndbrk(0x80);
}

void cmnd(unsigned char c)
{
	data=c;
	control&=~(1<<rs);
	control&=~(1<<rw);
	control|=(1<<en);
	_delay_ms(50);
	control&=~(1<<en);
	
}

void dat(unsigned char d)
{
	data=d;
	control|=(1<<rs);
	control&=~(1<<rw);
	control|=(1<<en);
	_delay_ms(50);
	control&=~(1<<en);
}


void cmndbrk(unsigned char r)
{
	unsigned char k;
	k=r&0xf0;
	cmnd(k);
	r=r<<4;
	k=r&0xf0;
	cmnd(k);
}

void datbrk(unsigned char o)
{
	unsigned char h;
	h=o&0xf0;
	dat(h);
	o=o<<4;
	h=o&0xf0;
	dat(h);
}

void str(unsigned char *s)
{
	while(*s)
	{
		datbrk(*s);
		s++;
		_delay_ms(50);
	}
	
}

void convert(unsigned int val,unsigned char pos)
{
	unsigned char i,value;
	for (i=0;i<4;i++)
	{
		value=val%10;
		val=val/10;
		cmndbrk(pos);
		datbrk(value+48);
		pos--;
	}
}
unsigned char keysense(void)
{
	while(1)
	{
		key&=~(1<<col1);
		key|=(1<<col2)|(1<<col3);
		
		if (bit_is_clear(keyin,row1))
		{
			return 1;
		}
		
		if (bit_is_clear(keyin,row2))
		{
			return 4;
		}
		
		if (bit_is_clear(keyin,row3))
		{
			return 7;
		}
		
		if (bit_is_clear(keyin,row4))
		{
			return 0;
		}
		
		key&=~(1<<col2);
		key|=(1<<col1)|(1<<col3);
		
		if (bit_is_clear(keyin,row1))
		{
			return 2;
		}
		
		if (bit_is_clear(keyin,row2))
		{
			return 5;
		}
		
		if (bit_is_clear(keyin,row3))
		{
			
			return 8;
		}
		
		if (bit_is_clear(keyin,row4))
		{
			
			return 0;
		}
		
		
		
		key&=~(1<<col3);
		key|=(1<<col1)|(1<<col2);
		
		if (bit_is_clear(keyin,row1))
		{
			return 3;
		}
		
		if (bit_is_clear(keyin,row2))
		{
			return 6;
		}
		
		if (bit_is_clear(keyin,row3))
		{
			return 9;
		}
		
		if (bit_is_clear(keyin,row4))
		{
			return 0;
		}
	}
}



int main(void)
{
	unsigned char k,a,b,c;
	unsigned int sum;
	DDRB&=~((1<<PB0)|(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6));
	DDRB|=(1<<PB0)|(1<<PB1)|(1<<PB2);
	PORTB|=(1<<PB3)|(1<<PB4)|(1<<PB5)|(1<<PB6);
	DDRD=0xff;
	lcd_init();
	while(1)
	{
		cmndbrk(0x01);
		cmndbrk(0x80);
		str("WELCOME TO HOTEL");
		cmndbrk(0xc2);
		str("TRANSYLVANIA");
		_delay_ms(50);
		cmndbrk(0x01);
		cmndbrk(0x80);
		str("1.CHICKEN-Rs.250");
		cmndbrk(0xc0);
		str("2.MUTUN-Rs.350");
		cmndbrk(0x90);
		str("3.NAAN-Rs.30");
		cmndbrk(0xd0);
		str("4.SABJI-Rs.60");
		_delay_ms(50);
		cmndbrk(0x01);
		cmndbrk(0x80);
		str("5.PARANTHA-Rs.50");
		cmndbrk(0xc0);
		str("6.DAAL-Rs.70");
		cmndbrk(0x90);
		str("7.PANEER-Rs.150");
		cmndbrk(0xd0);
		str("8.PAPAD-Rs.20");
		_delay_ms(50);
		cmndbrk(0x01);
		cmndbrk(0x83);
		str("ENTER YOUR");
		cmndbrk(0xc5);
		str("CHOICE");
		cmndbrk(0x96);
		k=keysense();
		datbrk(k+48);
		_delay_ms(1000);
		cmndbrk(0x01);
		switch(k)
		{
			case 1:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("1. CHICKEN");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("250");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-250;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs.frm counter   ");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc6);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 2:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("2. MUTTON");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("350");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-350;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 3:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("3. NAAN");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("30");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-30;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 4:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("4. SABJI");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("60");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-60;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 5:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("5. PARANTHA");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("50");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-50;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 6:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("6. DAAL");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("70");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-70;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 7:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("7. PANEER");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("150");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-150;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 8:
			cmndbrk(0x80);
			str("YOU HAVE SELECTD");
			cmndbrk(0xc0);
			str("8. PAPAD");
			cmndbrk(0x90);
			str("PLZ PAY RUPEE");
			cmndbrk(0xd5);
			str("20");
			_delay_ms(500);
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("AMT GIVEN- ");
			a=keysense();
			datbrk(a+48);
			_delay_ms(500);
			b=keysense();
			datbrk(b+48);
			_delay_ms(500);
			c=keysense();
			datbrk(c+48);
			_delay_ms(500);
			sum=100*a+10*b+c;
			sum=sum-20;
			cmndbrk(0x90);
			str("PLZ Collect ");
			cmndbrk(0xd0);
			str("Rs     frm counter");
			convert(sum,0xd5);
			_delay_ms(1000);
			cmndbrk(0x01);
			cmndbrk(0xc5);
			str("THANK YOU");
			_delay_ms(1000);
			break;
			case 9:
			cmndbrk(0x01);
			cmndbrk(0x80);
			str("NINE");
			cmndbrk(0xc8);
			str("9");
			_delay_ms(500);
			break;
		}
	}
}