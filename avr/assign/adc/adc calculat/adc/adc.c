

#include<avr/io.h>
#include<util/delay.h>
#include<string.h>
 
#define LCD PORTC
#define en PC2
#define rw PC1
#define rs PC0

void ADC_init(void);
unsigned int ADC_read(unsigned char);
void adc_conversion(uint16_t,unsigned char);
void lcd_cmd(unsigned char);
void lcd_cmd1(unsigned char);
void lcd_init(void);
void lcd_data(unsigned char);
void lcd_data1(unsigned char);
void lcd_str(unsigned char *);
void character(void);

int main(void)
{
   	unsigned int value;
	   unsigned char i;
	DDRC=0xFF;
	DDRD=0x07;
	
	lcd_init();
	ADC_init();	// Initialization of ADC
	lcd_str("ADC OUTPUT");
	//lcdcmd(0x8e);
	//lcdstr("WELCOME TO RIT");
	
	while(1)
	{

		/*for(i=0;i<24;i++)
		{
		lcdcmd(0x1c);
		_delay_ms(100);
		}
		for(i=0;i<24;i++)
		{
					
		lcdcmd(0x18);*/
		value=ADC_read(2);
		adc_conversion(value,0xc8);
			//_delay_ms(100);
	//	}		
	}
}		
void ADC_init(void)		// Initialization of ADC
{
	ADMUX|=(1<<REFS0)|(1<<REFS1);	// AVcc with external capacitor at AREF
	ADCSRA|=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);	
						// Enable ADC and set Prescaler division factor as 128
}
 
unsigned int ADC_read(unsigned char ch)
{
	ch= ch & 0b00000111;		// channel must be b/w 0 to 7
	ADMUX |= ch;				// selecting channel
 
	ADCSRA|=(1<<ADSC);			// start conversion
	while((ADCSRA & (1<<ADIF))==0);	// waiting for ADIF, conversion complete
	ADCSRA|=(1<<ADIF);			// clearing of ADIF, it is done by writing 1 to it
   	   return (ADC);
}

/* this function is written to convert integer value to their corresponding ASCII value*/
void adc_conversion(unsigned int adc_out,unsigned char position)  
{
	unsigned int adc_out1;
	int i=0;
	//unsigned char position=0xC3;
	for(i=0;i<=5;i++)
	{
		adc_out1=adc_out%10;
		adc_out=adc_out/10;
		lcd_cmd1(position);
		lcd_data1(48+adc_out1);
		position--;
	}
}

void lcd_init(void)
{
	lcd_cmd1(0x02);
	_delay_ms(10);
	lcd_cmd1(0x28);
	_delay_ms(10);
	lcd_cmd1(0x01);
	_delay_ms(10);
	lcd_cmd1(0x06);
	_delay_ms(10);
	lcd_cmd1(0x0e);
	_delay_ms(10);
	lcd_cmd1(0x80);
	_delay_ms(10);
}
void lcd_cmd(unsigned char value)
{
	LCD=value;
	LCD&=~(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(10);
	LCD&=~(1<<en);
	_delay_ms(10);
}
void lcd_cmd1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_cmd(cd1);
	cd1=(value<<4) & 0xf0;
	lcd_cmd(cd1);
}

void lcd_data(unsigned char value)
{
	LCD=value;
	LCD|=(1<<rs);
	LCD&=~(1<<rw);
	LCD|=(1<<en);
	_delay_ms(10);
	LCD&=~(1<<en);
	_delay_ms(10);

}
void lcd_data1(unsigned char value)
{
	unsigned char cd1;
	cd1=value & 0xf0;
	lcd_data(cd1);
	
	cd1=(value<<4) & 0xf0;
	lcd_data(cd1);
}

void lcd_str(unsigned char *s)
{
	while(*s)
	{
		lcd_data1(*s);
		s++;
		_delay_ms(100);
	}
}
/*void character()
{
	lcdcmd(64);  //Address where values of the first custom character is stored
	lcddata(23);
	lcddata(20);
	lcddata(20);
	lcddata(31);
	lcddata(5);
	lcddata(5);
	lcddata(29);
	lcddata(0);
	lcdcmd(0x87);  //Address of the location where the character is to be displayed
	lcddata(0);  // Displaying the character created at address 0x64
	_delay_ms(10);

/*	lcdcmd(72);
	lcddata(0);
	lcddata(0);
	lcddata(0);
	lcddata(10);
	lcddata(0);
	lcddata(4);
	lcddata(17);
	lcddata(14);
	lcdcmd(0x80);
	lcddata(1);
	_delay_ms(10);

	lcdcmd(80);
	lcddata(0);
	lcddata(0);
	lcddata(10);
	lcddata(0);
	lcddata(4);
	lcddata(0);
	lcddata(14);
	lcddata(17);
	lcdcmd(0x82);
	lcddata(2);
	_delay_ms(10);
	lcdcmd(88);
	lcddata(1);
	lcddata(3);
	lcddata(5);
	lcddata(9);
	lcddata(9);
	lcddata(11);
	lcddata(27);
	lcddata(24);
	lcdcmd(0x84);
	lcddata(3);
	_delay_ms(10);

	lcdcmd(96);
	lcddata(0);
	lcddata(10);
	lcddata(0);
	lcddata(31);
	lcddata(17);
	lcddata(14);
	lcddata(0);
	lcddata(0);
	lcdcmd(0x86);
	lcddata(4);
	_delay_ms(10);

	lcdcmd(104);
	lcddata(10);
	lcddata(0);
	lcddata(4);
	lcddata(0);
	lcddata(14);
	lcddata(17);
	lcddata(17);
	lcddata(14);
	lcdcmd(0xC2);
	lcddata(5);
	_delay_ms(10);

	lcdcmd(112);
	lcddata(0);
	lcddata(10);
	lcddata(0);
	lcddata(0);
	lcddata(4);
	lcddata(0);
	lcddata(31);
	lcddata(0);
	lcdcmd(0xC4);
	lcddata(6);
	_delay_ms(10);

	lcdcmd(120);
	lcddata(0);
	lcddata(17);
	lcddata(10);
	lcddata(17);
	lcddata(4);
	lcddata(0);
	lcddata(14);
	lcddata(17);
	lcdcmd(0xC6);
	lcddata(7);
	_delay_ms(10);
}*/
	
