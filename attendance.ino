// Arduino data logger with SD card and DHT11 humidity and temperature sensor
 
#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library
//#include <DHT.h>        // Include DHT sensor library
 
File dataFile;
 
// Initialize DHT library
 
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial)
    ; // wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while (1);
  }
  Serial.println("initialization done.");
  delay(2000);
}

void loop()
{
  
}













//int pin = 0;
//void setup() 
//{
//  pinMode(2, INPUT);
//  pinMode(3, OUTPUT);
//  pinMode(4, OUTPUT);
//}
//
//void loop() 
//{
//  digitalWrite(3, HIGH);
//  pin= digitalRead(2);
//  if(pin == HIGH)
//  {
//    digitalWrite(4, HIGH);
//  }
//}
