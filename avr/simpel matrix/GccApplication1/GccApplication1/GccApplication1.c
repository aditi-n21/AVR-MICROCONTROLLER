
#include <avr/io.h>
#include <util/delay.h>
int main(void)
{DDRD=0xff;
	DDRC=0xff;
	DDRA=0xff;
	int i=0;

//	unsigned char arr[]={0x7F, 0x49, 0x49, 0x49, 0x36,0x00,0x00,0x00};//for B
	while(1)
    {
		
			PORTC=0xfe;
			PORTD=0x7f;
			_delay_ms(10);
			PORTC=0xfd;
			PORTD=0x49;
			_delay_ms(10);
				PORTC=0xfb;
				PORTD=0x49;
				_delay_ms(10);
					PORTC=0xf7;
					PORTD=0x49;
					_delay_ms(10);
						PORTC=0xef;
						PORTD=0x36;
						_delay_ms(10);
						
	
}
	}