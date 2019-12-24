#include<SoftwareSerial.h>
#include<SPI.h>
#include<SD.h>

File file; //csv file reading
File sensorData; //csv file writing
int CS = 10; //chip select of uno in on 10
char location;

String dataString="";
String dataSerial;
String roll_id, name, finger_data;


void setup()
{
  Serial.begin(9600);
  //this is for write file
  pinMode(0, INPUT);
    while (!Serial); // wait for serial port to connect. Needed for native USB port only
  Serial.print("Initializing SD card...");
    if (!SD.begin()) 
    {
      Serial.println("initialization failed!");
      while (1);
    }
  Serial.println("initialization done.");
    delay(2000);

    //this is for read file
  if (!SD.begin(CS)) 
  {
      Serial.println("begin error");
      return;
    }
    file = SD.open("gps.csv", FILE_READ);
  if (!file) 
  {
      Serial.println("open error");
      return;
  }

  
  
}

void loop()
{
  //Serial.println("in loop");
  while(Serial.available())
  { 
    Serial.println("in while loop");
    dataSerial = Serial.readString();
    compare();

  }
}


//this is for reading csv file
bool readLine(File &f, char* line, size_t maxLen) {
  for (size_t n = 0; n < maxLen; n++) {
    int c = f.read();
    if ( c < 0 && n == 0) return false;  // EOF
    if (c < 0 || c == '\n') {
      line[n] = 0;
      return true;
    }
    line[n] = c;
  }
  return false; // line too long
}

//this is used for getting the desired column data
bool readVals(String* v1, String* v2, String* v3) {
  char line[200], *ptr, *str;
  if (!readLine(file, line, sizeof(line))) {
    return false;  // EOF or too long
  }
  *v1 = strtol(line, &ptr, 10);
  if (ptr == line) return false;  // bad number if equal
  while (*ptr) {
    if (*ptr++ == ',') break;
  }
  //strtol :- converts the contents of  string as an integral number of the specified base and return its value as a long int.
  *v2 = strtol(ptr, &str, 10);
  while (*ptr) {
    if (*ptr++ == ',') break;
  }
  *v3 = strtol(ptr, &str, 10);
  while (*ptr) {
    if (*ptr++ == ',') break;
  }
  String a = strtok_r(ptr, ",", &str);
  
  return str != ptr;  // true if number found
}



void compare()
{
  while(readVals(&roll_id, &name, &finger_data))
  {
    //comparing with database the received data
    if (dataSerial == roll_id)
    {
      store();
    }
    else
    {
      Serial.println("no match found");
    }
  }
}

void store()
{
  if(SD.exists("database_write.csv"))
  {
    sensorData = SD.open("database_write.csv", FILE_WRITE);
    if(sensorData)
    {
        sensorData.println(dataSerial);
        sensorData.println("dataSerial");
        sensorData.close();
    }
    else
    Serial.println("error opening csv file");
}

}
