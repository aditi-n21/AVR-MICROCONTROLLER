/*
 * i2c_m.c
 *
 * Created: 2/15/2014 10:00:23 AM
 *  Author: MANOJ
 */ 


#include <avr/io.h>
#include <util/delay.h>
#include <inttypes.h>

void TWI_start(void);
void TWI_repeated_start(void);
void TWI_init_master(void);
void TWI_write_address(unsigned char);
void TWI_read_address(unsigned char);
void TWI_write_data(unsigned char);
void TWI_read_data(void);
void TWI_stop(void);

unsigned char address=0x20,read=1,write=0;
unsigned char write_data=0x01,recv_data;

int main(void)
{
	//_delay_ms(2000);
	DDRB=0xff;
	DDRC=0xff;
	TWI_init_master();
    while(1)
    {
       if(write_data==0x00)
	       write_data=1;
		   
	TWI_start();
	TWI_write_address(address+write);
	TWI_write_data(write_data);
	TWI_stop();
	_delay_ms(10);
	
	TWI_start();
	TWI_read_address(address+read);
	TWI_read_data();
	TWI_stop();
	
	_delay_ms(100);
	write_data=write_data * 2;	   
    }
}

void TWI_init_master(void)
{
	TWBR=0x01;
	TWSR=(0<<TWPS1)|(0<<TWPS0);
}

void TWI_start()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x08);
}

void TWI_repeated_start()
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x10);
}
void TWI_write_address(unsigned char data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x18);
}
void TWI_read_address(unsigned char data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x40);
}
void TWI_write_data(unsigned char data)
{
	TWDR=data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x28);
}
void TWI_read_data()
{
	TWCR=(1<<TWINT)|(1<<TWEN);
	while(!(TWCR & (1<<TWINT)));
	while((TWSR & 0xf8)!= 0x58);
	recv_data=TWDR;
	PORTB=recv_data;
}

void TWI_stop()
{
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
	while(!(TWCR & (1<<TWSTO)));
	
}
