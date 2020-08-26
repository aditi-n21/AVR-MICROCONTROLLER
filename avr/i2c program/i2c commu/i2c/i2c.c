/*
 * i2c.c
 *
 * Created: 7/28/2016 5:03:56 AM
 *  Author: vipul
 */ 


#include <avr/io.h>
void i2c_write(unsigned char data)
{
	TWDR =data;
	TWCR|=((1<<TWINT)|(1<<TWEN));
	while((TWCR&(1<<TWINT))==0);
}
void i2c_start(void)
{
	TWCR|=((1<<TWINT)|(1<<TWSTA)|(1<<TWEN));
	while((TWCR&(1<<TWINT))==0);
}
void i2c_stop(void)
{
	
	TWCR|=((1<<TWINT)|(1<<TWSTO)|(1<<TWEN));
}
void i2c_inti(void)
{
	TWSR=0x00;
	TWBR=0x47;
	TWCR=0x04;
}
int main(void)
{
	i2c_inti();
	i2c_start();
	i2c_write(0b11010000);
	i2c_write(0b00111111);
	i2c_stop();
    while(1);
}