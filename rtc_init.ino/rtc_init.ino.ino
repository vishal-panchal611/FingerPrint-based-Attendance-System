#include <Wire.h>
#include "RTClib.h"

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup () 
{
  Serial.begin(9600);
  delay(2000); // wait for console opening

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");
  
  // Comment out below lines once you set the date & time.
    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
    // Following line sets the RTC with an explicit date & time
    // for example to set January 27 2017 at 12:56 you would call:
    // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));
  }
}

void loop () 
{
    DateTime now = rtc.now();
    
    //Serial.println("Current Date & Time: ");
    Serial.print(now.year(),DEC);
    //Serial.print('/');
    Serial.print(now.month(), DEC);
    //Serial.print('/');
    Serial.print(now.day(), DEC);
    //Serial.print('-');
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    //Serial.print('-');
    Serial.print(now.hour(), DEC);
    //Serial.print(':');
    Serial.print(now.minute(), DEC);
    //Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
    
    
    Serial.println();
    delay(1000);
}




//#include<DS3231.h>
////#define SDA A5 
////#define SCL A4
//DS3231 rtc(SDA, SCL);
//  
//void setup() 
//{
//  Serial.begin(115200);
//  rtc.begin();
//  rtc.setDOW(Friday);
//  rtc.setTime(11, 22, 0);
//  rtc.setDate(27, 12, 2019);    
//}
//
//void loop() 
//{
//  Serial.print(rtc.getDOWstr());
//  Serial.print("");
//  Serial.println(rtc.getDateStr());
//  Serial.println("--");
//  Serial.println(rtc.getTimeStr());
//  delay(1000);
//}
