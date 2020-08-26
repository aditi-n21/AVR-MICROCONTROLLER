/*
 * i2c_slave.c
 *
 * Created: 7/28/2016 5:17:57 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
unsigned char i2c_read()
{
		TWCR=(1<<TWINT)|(1<<TWEN);
		while((TWCR&(1<<TWINT))==0);
		return TWDR;
	
}
void i2c_write(unsigned char data)
{
	TWDR =data;
	TWCR=(1<<TWINT)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}
void i2c_start(void)
{
	TWCR=(1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	while((TWCR&(1<<TWINT))==0);
}
void i2c_stop(void)
{
	
	TWCR=(1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
}
void i2c_inti(void)
{
	TWSR=0x00;
	TWBR=0x47;
	TWCR=0x04;
}
int main(void)
{unsigned char i=0;
	DDRA=0xff;
	i2c_inti();
	i2c_start();
	i2c_write(0b11011011);
	i=i2c_read();
	PORTA=i;
	i2c_stop();
    while(1);
}