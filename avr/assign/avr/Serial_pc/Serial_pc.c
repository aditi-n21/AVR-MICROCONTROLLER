/*
 * Serial_pc.c
 *
 * Created: 16-08-2012 PM 3:29:55
 *  Author: MANOJ
 */ 

// Program to receive data from USART and displaying that..
// data on LCD and sending the same data on HyperTerminal. 
/*
get data from serial port and displaying it on LCD and send back to the HyperTerminal
LCD DATA port----PORT A
ctrl port------PORT B
	rs-------PB0
	rw-------PB1
	en-------PB2
@ external clock frequency 12MHz
*/
 
#define F_CPU 8000000UL
 
//#define USART_BAUDRATE 9600
//#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)
 
#include<avr/io.h>
#include<util/delay.h>
 
#define LCD_DATA PORTA			// LCD data port
#define ctrl PORTB
#define en PB2		// enable signal
#define rw PB1		// read/write signal
#define rs PB0		// register select signal
//#define RX PD0
 
void LCD_cmd(unsigned char cmd);
void init_LCD(void);
void LCD_write(unsigned char data);
void LCD_clear();
 
void usart_init();
void usart_putch(unsigned char send);
unsigned int usart_getch();
 
int main()
{
	unsigned char i,value;
	
	DDRB=0xff;		
	DDRA=0xff;
	DDRD=0xfe;	
	DDRC=0xff;
	usart_init();		// initialization of USART
	init_LCD();		//initialization of LCD
	//_delay_ms(50);		// delay of 50 mili seconds
	while(1)
	{
		//usart_putch('A'
		//usart_putch('B');
		//usart_putch('C');
		//usart_putch('D');
		LCD_cmd(0x01);
		for(i=0;i<16;i++)
		{
		value=usart_getch();	// get data from serial port
		LCD_write(value);
		usart_putch(value);
		}		
		// write data to LCD
		//LCD_cmd(0x80);
		//LCD_write('H');
		//LCD_write('I');
		//_delay_ms(50);
		//usart_putch(value);
		//usart_putch(value);
		//usart_putch('\r');
		//usart_putch('\n');
		//usart_putch('H');		// send data back to the PC (HyperTerminal)
		//usart_putch('I');
		_delay_ms(50);
		
	//	LCD_write('B');
	//	LCD_write('E');
	//	_delay_ms(50);
		
	}
	return 0;
}
 
void init_LCD(void)
{
	LCD_cmd(0x38);		//initialization of 16X2 LCD in 8bit mode
	_delay_ms(1);
 
	LCD_cmd(0x01);		// clear LCD
	_delay_ms(1);
 
	LCD_cmd(0x0E);		// cursor ON
	_delay_ms(1);
	LCD_cmd(0x06);
	_delay_ms(1);
 
	LCD_cmd(0x80);		// ---8 go to first line and --0 is for 0th position
	_delay_ms(1);
	return;
}
 
void LCD_cmd(unsigned char cm)
{
	LCD_DATA=cm;
	ctrl =(0<<rs)|(0<<rw)|(1<<en);	
	_delay_ms(1);
	ctrl =(0<<rs)|(0<<rw)|(0<<en);	
	_delay_ms(10);
	return;
}
 
void LCD_write(unsigned char dat)
{
	LCD_DATA= dat;
	ctrl = (1<<rs)|(0<<rw)|(1<<en);	
	_delay_ms(1);
	ctrl = (1<<rs)|(0<<rw)|(0<<en);	
	_delay_ms(10);	
	return ;
}
 
void usart_init()
{
	UCSRB |= (1 << TXEN) | (1 << RXEN);   
					// Turn on the transmission and reception circuitry
	//UCSRC |= (1 << URSEL) | (1<<USBS) | (1 << UCSZ0) | (1 << UCSZ1); 
	UCSRC |= (1 << URSEL) | (1 << UCSZ0) | (1 << UCSZ1);
					// Use 8-bit character sizes
    UBRRL=51;
	//UBRRL = BAUD_PRESCALE; // Load lower 8-bits of the baud rate value..
							// into the low byte of the UBRR register
	//UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
									// into the high byte of the UBRR register
}
 
void usart_putch(unsigned char send)
{
	
	while(!(UCSRA & (1 << UDRE))); 
	// Do nothing until UDR is ready..
					 		// for more data to be written to it
	UDR = send; // Send the byte 
}
unsigned int usart_getch()
{
	while ((UCSRA & (1 << RXC)) == 0);				// Do nothing until data have been received and is ready to be read from UDR
		return(UDR); // return the byte

//PORTC=UDR;
}