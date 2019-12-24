#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>

/* CSV File Reading */
File file;
int SC = 10;  //SC - Pin 10 Arduino uno
char location;

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
/* Close CSV File Reading */

void setup()  
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  //SD Card Reader Setup
  Serial.begin(9600);
  if (!SD.begin(SC)) {
    Serial.println("begin error");
    return;
  }
  file = SD.open("gps.CSV", FILE_READ);
  if (!file) {
    Serial.println("open error");
    return;
  }
  
}

void loop() // run over and over
{ 
String roll_id, name, finger_data;

  while (readVals(&roll_id, &name, &finger_data)) 
  {
    
    //First 4 Long datatype variables 
    // Serial.println(roll_id);
    // Serial.println(name);
    Serial.println(finger_data);
    
  } 
 
}
