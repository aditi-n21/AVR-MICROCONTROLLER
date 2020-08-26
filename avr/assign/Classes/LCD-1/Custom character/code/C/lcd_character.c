 #include<reg51.h>
sfr lcd_data_pin=0x80; 
sbit rs=P3^5;  //Register select pin
sbit rw=P3^6;  // Read write pin
sbit en=P3^7;  //Enable pin

void delay(unsigned int count)  // Function to provide time delay in msec.
{
int i,j;
for(i=0;i<count;i++)
  for(j=0;j<1275;j++);
}

void lcd_command(unsigned char comm)  //Function to send commands to LCD.
{
lcd_data_pin=comm;
en=1; 
rs=0; 
rw=0; 
delay(1);
en=0;
}

void lcd_data(unsigned char disp)  //Function to send data to LCD
{
lcd_data_pin=disp;
en=1; 
rs=1; 
rw=0; 
delay(1);
en=0;
}

void lcd_ini()  //Function to initialize the LCD
{
lcd_command(0x38);  
delay(2);
lcd_command(0x0F); 
delay(2);
lcd_command(0x82);  //Set cursor to blink at line 1 positon 2
delay(2);
}

void character()
{
lcd_command(64);  //Address where values of the first custom character is stored
lcd_data(0);
lcd_data(10);
lcd_data(21);
lcd_data(17);
lcd_data(10);
lcd_data(4);
lcd_data(0);
lcd_data(0);
lcd_command(0xC0);  //Address of the location where the character is to be displayed
lcd_data(0);  // Displaying the character created at address 0x64 
delay(10);

lcd_command(72);
lcd_data(0);
lcd_data(0);
lcd_data(0);
lcd_data(10);
lcd_data(0);
lcd_data(4);
lcd_data(17);
lcd_data(14);
lcd_command(0x80);
lcd_data(1);
delay(10);

lcd_command(80);
lcd_data(0);
lcd_data(0);
lcd_data(10);
lcd_data(0);
lcd_data(4);
lcd_data(0);
lcd_data(14);
lcd_data(17);
lcd_command(0x82);
lcd_data(2);
delay(10);
lcd_command(88);
lcd_data(1);
lcd_data(3);
lcd_data(5);
lcd_data(9);
lcd_data(9);
lcd_data(11);
lcd_data(27);
lcd_data(24);
lcd_command(0x84);
lcd_data(3);
delay(10);

lcd_command(96);
lcd_data(0);
lcd_data(10);
lcd_data(0);
lcd_data(31);
lcd_data(17);
lcd_data(14);
lcd_data(0);
lcd_data(0);
lcd_command(0x86);
lcd_data(4);
delay(10);

lcd_command(104);
lcd_data(10);
lcd_data(0);
lcd_data(4);
lcd_data(0);
lcd_data(14);
lcd_data(17);
lcd_data(17);
lcd_data(14);
lcd_command(0xC2);
lcd_data(5);
delay(10);

lcd_command(112);
lcd_data(0);
lcd_data(10);
lcd_data(0);
lcd_data(0);
lcd_data(4);
lcd_data(0);
lcd_data(31);
lcd_data(0);
lcd_command(0xC4);
lcd_data(6);
delay(10);

lcd_command(120);
lcd_data(0);
lcd_data(17);
lcd_data(10);
lcd_data(17);
lcd_data(4);
lcd_data(0);
lcd_data(14);
lcd_data(17);
lcd_command(0xC6);
lcd_data(7);
delay(10);
}

void main()
{
lcd_ini();
character();
}