// Arduino data logger with SD card and DHT11 humidity and temperature sensor
 
#include <SPI.h>        // Include SPI library (needed for the SD card)
#include <SD.h>         // Include SD library
#include <DHT.h>        // Include DHT sensor library
 
#define DHTPIN 4            // DHT11 data pin is connected to Arduino pin 4
#define DHTTYPE DHT11       // DHT11 sensor is used
DHT dht(DHTPIN, DHTTYPE);   // Initialize DHT library

File sensorData;
String dataString="";
String st;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  pinMode(0, INPUT);
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
 
uint16_t line = 1;
 
void loop() 
{
  delay(1000);
  // Read humidity
  savedata();
  delay(2000);
}    

void savedata()
{
    Serial.println("in savedata");
  while(Serial.available())
  {
      st = Serial.readString();
        Serial.println(st);
        csv();
  }
}

void csv()
{
    if(SD.exists("gps.csv"))
          {
            sensorData = SD.open("gps.csv", FILE_WRITE);
            if(sensorData)
            {
                sensorData.println(st);
                sensorData.close();
            }
            else
            Serial.println("error opening csv file");
          }
}

  
