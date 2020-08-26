/*
 * keypad.c
 *
 * Created: 02-01-2014 PM 3:36:57
 *  Author: MANOJ
 */ 

#include <avr/io.h>
#include <util/delay.h>
#define RS PB5
#define RW PB6
#define EN PB7
#define row1 PA0
#define row2 PA1
#define row3 PA2
#define row4 PA3
#define col1 PA4
#define col2 PA5
#define col3 PA6

void lcd(void);
void writecmd(unsigned char);
void writedata(unsigned char);
void writestr(unsigned char *s);
unsigned char keysense(void);

unsigned char keysense(void)
{ 
	while(1)
	{
		PORTA&=~(1<<col1);
		//PORTA=0b11101111;
		PORTA|=(1<<col2)|(1<<col3);
		if(bit_is_clear(PINA,row1))	
			//writestr("KEY 1");
			return(1);
		else if(bit_is_clear(PINA,row2))
			//writestr("KEY 4");
			return(4);
		else if(bit_is_clear(PINA,row3))
			//writestr("KEY 7");
			return(7);
		else if(bit_is_clear(PINA,row4))
			//writestr("KEY *");
			return('*');
			_delay_ms(50);
		PORTA&=~(1<<col2);
		PORTA|=(1<<col1)|(1<<col3);
		//PORTA=0b11011111;
		if(bit_is_clear(PINA,row1))
			return(2);
		else if(bit_is_clear(PINA,row2))
			return(5);
		else if(bit_is_clear(PINA,row3))
			return(8);
		else if(bit_is_clear(PINA,row4))
			return(0);		
			_delay_ms(50);
		PORTA&=~(1<<col3);
		PORTA|=(1<<col2)|(1<<col1);
		//PORTA=0b10111111;
		if(bit_is_clear(PINA,row1))
			return(3);
		else if(bit_is_clear(PINA,row2))
			return(6);
		else if(bit_is_clear(PINA,row3))
			return(9);
		else if(bit_is_clear(PINA,row4))
			return('#');
		_delay_ms(50);
	};
}	 

void writestr(unsigned char *s)
{	
	unsigned char l,i;
	l=strlen(s);
	for(i=0;i<l;i++)
	{
		writedata(*s);
		s++;
		_delay_ms(50);
	}
}

void writecmd(unsigned char a)
{
	PORTB=(0<<RS)|(0<<RW)|(1<<EN);
	PORTC=a;
	_delay_ms(5);
	PORTB=(0<<RS)|(0<<RW)|(0<<EN);
	return;
}

void writedata(unsigned char b)
{
	PORTB=(1<<RS)|(0<<RW)|(1<<EN);
	PORTC=b;
	_delay_ms(5);
	PORTB=(1<<RS)|(0<<RW)|(0<<EN);
	return;
}
void lcd(void)
{
	writecmd(0x38);
	writecmd(0x0e);
	writecmd(0x01);
	writecmd(0x06);
	writecmd(0x80);
}

int main()
{
	unsigned char a;
	char arr[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};
	DDRA=0xf0;
	PORTA=0x0f;
	DDRC=0XFF;
	DDRD=0XFF;
	DDRB=0XE0;
	lcd();
	writestr("WELCOME");
	writecmd(0xc5);
	writestr("	  CETPA");
	writecmd(0x01);
/*	writestr("MANOJ");
	writecmd(0xc5);
	writestr("KUMAR");
	writecmd(0x01);
	writestr("KEY SENSED");	
	writecmd(0xc6);
	writedata('A');
	keysense();		 */
 
	while(1)
	{
	 writecmd(0x80);
	writestr("KEY SENSED");	
	//value=PINA;
	//if(PINA!=0x0f)
	//{
	a=keysense();
	switch(a)
	{
   case 0: 
			PORTD=arr[a];
			_delay_ms(10);
			writecmd(0xc5);
			writestr("KEY 0");
			_delay_ms(50);
			break;
	case 1: writecmd(0xc5);
		PORTD=arr[a];
		_delay_ms(10);
			writestr("KEY 1");
			_delay_ms(50);
			break;
	case 2: writecmd(0xc5);
		PORTD=arr[a];
		_delay_ms(10);
			writestr("KEY 2");
			_delay_ms(50);
			break;
    case 3: writecmd(0xc5);
			PORTD=arr[a];
		_delay_ms(10);
			writestr("KEY 3");
			_delay_ms(50);
			break;
	case 4:  writecmd(0xc5);
			PORTD=arr[a];
			_delay_ms(10);
			writestr("KEY 4");
			_delay_ms(50);
			break;
	case 5:   writecmd(0xc5);
			PORTD=arr[a];
			_delay_ms(10);
			writestr("KEY 5");
			_delay_ms(50);
			break;
	case 6:  writecmd(0xc5);
			PORTD=arr[a];
			_delay_ms(10);
			writestr("KEY 6");
			_delay_ms(50);
			break;
	case 7:  writecmd(0xc5);
			PORTD=arr[a];
			_delay_ms(10);
			writestr("KEY 7");
			_delay_ms(50);
			break;
	case 8:  writecmd(0xc5);
			PORTD=arr[a];
			writestr("KEY 8");
			_delay_ms(50);
			break;
	case 9: writecmd(0xc5);
			PORTD=arr[a];
			writestr("KEY 9");
            _delay_ms(50);
			break;
	default:
			break;

	}
  //}
}  
return 0;
}
