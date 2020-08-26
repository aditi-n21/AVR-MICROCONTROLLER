#include <Wire.h>
#include "RTClib.h"
#include <LiquidCrystal.h>
RTC_DS1307 RTC;
LiquidCrystal lcd (7,6,5,4,3,2);
int a,b;
void setup () 
{
   DateTime now = RTC.now();
  Serial.begin(9600);
  lcd.begin(20, 4);
   Wire.begin();
  RTC.begin();
     
   lcd.setCursor(0,0);
   lcd.print("  SHRI RAM GROUP OF   ");
   lcd.setCursor(0,1);
   lcd.print("     COLLEGES    ");
   lcd.setCursor(0,2);
   lcd.print("   MUZAFFARNAGAR   ");
   lcd.setCursor(0,3);
   lcd.print("   UTTAR PRADESH ");

   delay(2000);
   
    lcd.setCursor(0,2);
   lcd.print("  LECTURE - DCN ");
   lcd.setCursor(0,3);
   lcd.print(" PUSHPENDER SAINI ");
 
   
 
  if (! RTC.isrunning())
  {
    Serial.println("RTC is NOT running!");
    RTC.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
}


void loop () 
{
    DateTime now = RTC.now();
    
    lcd.setCursor(1,0);
    lcd.print("TIME: ");
    lcd.print(now.hour(), DEC);
    lcd.print(" : ");
    lcd.print(now.minute(), DEC);
    lcd.print(" : ");
    lcd.print(now.second(), DEC); 
    a=now.hour();
    b=now.minute();
    if(a==9&&b==55)
    {
   lcd.setCursor(0,2);
   lcd.print("   LECTURE - OC  ");
   lcd.setCursor(0,3);
   lcd.print("   NISHA CHACHUN  ");
    }
    if(a==9&&b==55)
    {
   lcd.setCursor(0,2);
   lcd.print("   LECTURE - DIP  ");
   lcd.setCursor(0,3);
   lcd.print("    PRAVEEN SIR  ");
    }
     if(a==9&&b==55)
    {
   lcd.setCursor(0,2);
   lcd.print("  LECTURE - VLSI  ");
   lcd.setCursor(0,3);
   lcd.print("   NISHA CHACHUN  ");
    }
     if(a==9&&b==55)
    {
   lcd.setCursor(0,2);
   lcd.print("   LECTURE - ED  ");
   lcd.setCursor(0,3);
   lcd.print("    ALOK GUPTA  ");
    }
    if(a==9&&b==55)
    {
    lcd.setCursor(0,2);
   lcd.print("   ECE DEPARTEMENT  ");
   lcd.setCursor(0,3);
   lcd.print("       LUNCH     ");
    }
    if(a==9&&b==55)
    {
   lcd.setCursor(0,2);
   lcd.print("   ECE DEPARTEMENT  ");
   lcd.setCursor(0,3);
   lcd.print("     LAB-PROJECT   ");
    }
     
    lcd.setCursor(1,1);
    lcd.print("DATE: ");
    lcd.print(now.day(), DEC);
    lcd.print(" / ");
    lcd.print(now.month(), DEC);
    lcd.print(" /");
    lcd.print(now.year(), DEC);
    delay(1000);
    
}
