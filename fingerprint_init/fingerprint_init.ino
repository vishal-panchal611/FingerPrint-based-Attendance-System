//=========================================================================//
//                                                                         //
//  ## R30X Fingerprint Sensor Library Example 1 ##                        //
//                                                                         //
//  Filename : R30X_Fingerprint_Test.ino                                   //
//  Description : Arduino compatible test program for Fingerprint_VMA      //
//                library for R30X series fingerprint sensors.             //
//  Library version : 1.0.1                                                //
//  Author : Vishnu M Aiea                                                 //
//  Src : https://github.com/vishnumaiea/R30X-Fingerprint-Sensor-Library   //
//  Author's website : https://www.vishnumaiea.in                          //
//  Initial release : IST 07:35 PM, 08-04-2019, Monday                     //
//  License : MIT                                                          //
//                                                                         //
//  Last modified : IST 11:44 PM, 08-04-2019, Monday                       //
//                                                                         //
//=========================================================================//
//#include "R30X_Fingerprint.h"
//=========================================================================//
//initialize the object with the correct password and address
//if you want to use the deafault values, pass nothing
//Serial1 is availabel only for Due and Mega. Pass SoftwareSerial object for Uno etc
//R30X_Fingerprint fps = R30X_Fingerprint (&Serial1, 0xFFFFFFFF, 0xFFFFFFFF); //custom password and address
// R30X_Fingerprint fps = R30X_Fingerprint (&Serial1); //use deafault password and address
//========================================================================//
//this implements the fingerprint enrolling process
//simply send the location of where you want to save the new fingerprint.
//the location can be from #1 to #1000
//the library location actually starts at 0, but I have made it to 1 to avoid confusion
//therefore a 1 will be substracted from your location automatically
//The finger needs to be scanend twice at steps #1 and #2
// uint8_t enrollFinger(uint16_t location) {
//   //enroll new fingerprint
//   debugPort.println("=========================");
//   debugPort.println("Enrolling New Fingerprint");
//   debugPort.println("=========================");
//   if((location > 1000) || (location < 1)) { //if not in range (1-1000)
//     debugPort.println();
//     debugPort.println("Enrolling failed.");
//     debugPort.println("Bad location.");
//     debugPort.print("location = #");
//     debugPort.println(location);
//     debugPort.println("Please try again.");
//     return 1;
//   }
//   delay(4000);
//   debugPort.println();
//   debugPort.println("Scan #1: Please put your finger on the sensor.");
//   debugPort.println();
//   delay(5000);
//   uint8_t response = fps.generateImage(); //scan the finger
//   if(response != 0) {
//     debugPort.println("Scan #1: ERROR - Scanning failed. Please try again.");
//   }
//   else {
//     debugPort.println("Scan #1: Scanning success.");
//     debugPort.println();
//     delay(2000);
//     response = fps.generateCharacter(1);  //generate the character file from image and save to buffer 1
//     if(response != 0) {
//       debugPort.println("Scan #1: ERROR - Template generation failed. Please try again.");
//     }
//     else {
//       debugPort.println();
//       debugPort.println("Scan #1: Template generation success.");
//       delay(2000);
//       debugPort.println("Scan #2: Please put your finger on the sensor.");
//       delay(5000);
//       debugPort.println();
//       response = fps.generateImage(); //scan the finger for second time
//       if(response != 0) {
//         debugPort.println("Scan #2: ERROR - Scanning failed. Please try again.");
//       }
//       else {
//         debugPort.println();
//         debugPort.println("Scan #2: Scanning success.");
//         delay(2000);
//         response = fps.generateCharacter(2);  //generate the character file from image and save to buffer 2
//         if(response != 0) {
//           debugPort.println("Scan #2: Template generation failed. Please try again.");
//         }
//         else {
//           debugPort.println();
//           response = fps.generateTemplate();  //combine the two buffers and generate a template
//           if(response == 0) {
//             debugPort.println();
//             response = fps.saveTemplate(1, location); //save the template to the specified location in library
//             if(response == 0) {
//               debugPort.print("-- Fingerprint enrolled at ID #");
//               debugPort.print(location);
//               debugPort.println(" successfully --");
//             }
//           }
//           else if(response == FPS_RESP_ENROLLMISMATCH) {
//             debugPort.println("ERROR : Fingerprints do not belong to same finger. Please try again.");
//           }
//         }
//       }
//     }
//   }
//   debugPort.println();
// }
// //=========================================================================//
// //Arduino setup function
// void setup() {
//   Serial.begin(115200);
//   fps.begin(115200);
//   Serial.println();
//   Serial.println("R307 Fingerprint Test");
//   Serial.println("======================");
//   Serial.println();
//   //you need to verify the password before you can do anything else
//   Serial.println("Verifying password..");
//   uint8_t response = fps.verifyPassword(0xFFFFFFFF);
//   Serial.println();
//   //this is optional
//   Serial.println("Setting new address..");
//   response = fps.setAddress(0xFFFFFFFF);
//   Serial.println();
// }
// //=========================================================================//
// //infinite loop
// void loop() {
//   uint8_t response = 0;
//   String inputString = "";
//   String commandString = "";
//   String firstParam = "";
//   String secondParam = "";
//   String thirdParam = "";
//   //send commands and parameters for each operation
//   //items are separated by single whitespace
//   //you can send up to 3 parameters
//   if(Serial.available()) {  //monitor the serial interface
//     inputString = Serial.readString();  //read the contents of serial buffer as string
//     Serial.print("Command : ");
//     Serial.println(inputString);
//     Serial.println();
//     //-------------------------------------------------------------------------//
//     uint8_t posCount = 0;
//     int indexOfSpace = 0;
//     while(inputString.indexOf(" ") != -1) { //loop until all whitespace chars are found
//       indexOfSpace = inputString.indexOf(" ");  //get the position of first whitespace
//       if(indexOfSpace != -1) {  //if a whitespace is found
//         if(posCount == 0) //the first one will be command string
//           commandString = inputString.substring(0, indexOfSpace); //end char is exclusive
//         if(posCount == 1) //second will be second param
//           firstParam = inputString.substring(0, indexOfSpace);
//         if(posCount == 2) //and so on
//           secondParam = inputString.substring(0, indexOfSpace);
//         else if(posCount == 3)
//           thirdParam = inputString.substring(0, indexOfSpace);
//         inputString = inputString.substring(indexOfSpace+1);  //trim the input string
//         posCount++;
//       }
//     }
//     //saves the last part of the string is no more whitespace is found
//     if(posCount == 0) //if there's just the command
//       commandString = inputString;
//     if(posCount == 1)
//       firstParam = inputString;
//     if(posCount == 2)
//       secondParam = inputString;
//     if(posCount == 3)
//       thirdParam = inputString;
//     //-------------------------------------------------------------------------//
//     //separate and print the received command and parameters
//     Serial.print("Command string = ");
//     Serial.println(commandString);
    
//     if(firstParam != "") {
//       Serial.print("First param = ");
//       Serial.println(firstParam);
//     }
//     if(secondParam != "") {
//       Serial.print("Second param = ");
//       Serial.println(secondParam);
//     }
//     if(thirdParam != "") {
//       Serial.print("Third param = ");
//       Serial.println(thirdParam);
//     }
    
//     Serial.println();
//     //-------------------------------------------------------------------------//
//     //deletes all the templates in the library
//     //this command has no parameters
//     //eg. clrlib
//     if(commandString == "clrlib") {
//       response = fps.clearLibrary();
//     }
//     //-------------------------------------------------------------------------//
//     //get templates count
//     //eg. tmpcnt
//     else if(commandString == "tmpcnt") {
//       Serial.println("Reading templates count..");
//       response = fps.getTemplateCount();
//     }
//     //-------------------------------------------------------------------------//
//     //read system parameters
//     //eg. readsys
//     else if(commandString == "readsys") {
//       response = fps.readSysPara();
//     }
//     //-------------------------------------------------------------------------//
//     //set data length
//     //this command has a single parameter
//     //value should be 32, 64, 128 or 256
//     //eg. setdatlen 256
//     else if(commandString == "setdatlen") {
//       uint16_t length = firstParam.toInt();
//       response = fps.setDataLength(length);
//     }
//     //-------------------------------------------------------------------------//
//     //capture and range search library
//     //this command has three parameters
//     //eg. capranser 3000 1 10
//     else if(commandString == "capranser") {
//       uint16_t timeOut = firstParam.toInt();  //first parameter in milliseconds
//       uint16_t startLocation = secondParam.toInt(); //second parameter
//       uint16_t count = thirdParam.toInt();  //third parameter
//       Serial.println("Capture and range search fingerprint..");
//       delay(1000);
//       Serial.println("Put your finger on the sensor..");
//       delay(3000);
//       response = fps.captureAndRangeSearch(timeOut, startLocation, count);
//     }
//     //-------------------------------------------------------------------------//
//     //capture and full search library
//     //eg. capfulser
//     else if(commandString == "capfulser") {
//       Serial.println("Capture and full search fingerprint..");
//       delay(1000);
//       Serial.println("Put your finger on the sensor..");
//       delay(3000);
//       response = fps.captureAndFullSearch();
//     }
//     //-------------------------------------------------------------------------//
//     //enroll a new fingerprint
//     //you need to scan the finger twice
//     //follow the on-screen instructions
//     //eg. enroll
//     else if(commandString == "enroll") {
//       uint16_t location = firstParam.toInt(); //converts String object to int
//       enrollFinger(location);
//     }
//     //-------------------------------------------------------------------------//
//     //verify 4 byte password
//     //password should be sent as hex string
//     //eg. verpwd FF16FF16
//     else if(commandString == "verpwd") {
//       const char* hexString = firstParam.c_str(); //convert String object to C-style string
//       uint32_t password = strtol(hexString, NULL, 16);  //convert hex formatted C-style string to int value
//       response = fps.verifyPassword(password);
//     }
//     //-------------------------------------------------------------------------//
//     //set 4 byte password sent in hex format
//     //password should be sent as hex string
//     //eg. setpwd FF16FF16
//     else if(commandString == "setpwd") {
//       const char* hexString = firstParam.c_str(); //convert String object to C-style string
//       uint32_t password = strtol(hexString, NULL, 16);  //convert hex formatted C-style string to int value
//       response = fps.setPassword(password);
//     }
//     //-------------------------------------------------------------------------//
//     //set 4 byte address sent in hex format
//     //address should be sent as hex string
//     //eg. setaddr FF16FF16
//     else if(commandString == "setaddr") {
//       const char *hexString = firstParam.c_str(); //convert String object to C-style string
//       uint32_t address = strtol(hexString, NULL, 16);  //convert hex formatted C-style string to int value
//       response = fps.setAddress(address);
//     }
//     //-------------------------------------------------------------------------//
//     //set baudrate
//     //baudrate must be integer multiple of 96000. max is 115200
//     //eg. setbaud 115200
//     else if(commandString == "setbaud") {
//       uint32_t baudrate = firstParam.toInt();
//       response = fps.setBaudrate(baudrate);
//     }
//     //-------------------------------------------------------------------------//
//     //set security level
//     //security level value must be 1-5
//     //deafault is usually 2
//     //eg. setseclvl 4
//     else if(commandString == "setseclvl") {
//       uint8_t level = firstParam.toInt();
//       response = fps.setSecurityLevel(level);
//     }
//     //-------------------------------------------------------------------------//
//     //scan finger image and save to image buffer
//     //eg. genimg
//     else if(commandString == "genimg") {
//       response = fps.generateImage();
//     }
//     //-------------------------------------------------------------------------//
//     //generate character file from image
//     //buffer Id should be 1 or 2
//     //eg. genchar 1
//     else if(commandString == "genchar") {
//       uint8_t bufferId = firstParam.toInt();
//       response = fps.generateCharacter(bufferId);
//     }
//     //-------------------------------------------------------------------------//
//     //generate template from char buffers
//     //template is the digital format of a fingerprint
//     //generated template will be available on both buffers 1 and 2
//     //eg. gentmp
//     else if(commandString == "gentmp") {
//       response = fps.generateTemplate();
//     }
//     //-------------------------------------------------------------------------//
//     //save template on buffer to library
//     //buffer ID should be 1 or 2
//     //location should be #1 - #10000 (don't send the "#" with command)
//     //eg. savtmp 1 32
//     else if(commandString == "savtmp") {
//       uint8_t bufferId = firstParam.toInt();
//       uint16_t location = secondParam.toInt();
//       response = fps.saveTemplate(bufferId, location);
//     }
//     //-------------------------------------------------------------------------//
//     //load template from library to buffer 1 or 2
//     //buffer ID should be 1 or 2
//     //location should be #1 - #10000 (don't send the "#" with command)
//     //eg. lodtmp 1 32
//     else if(commandString == "lodtmp") {
//       uint8_t bufferId = firstParam.toInt();
//       uint16_t location = secondParam.toInt();
//       response = fps.loadTemplate(bufferId, location);
//     }
//     //-------------------------------------------------------------------------//
//     //delete one or more templates from library
//     //to delete a single template, simply send 1 as quantity or count
//     //eg. deltmp 5 1
//     else if(commandString == "deltmp") {
//       uint16_t startLocation = firstParam.toInt();  //start location in library
//       uint16_t count = secondParam.toInt(); //quantity to delete
//       response = fps.deleteTemplate(startLocation, count);
//     }
//     //-------------------------------------------------------------------------//
//     //precisely match templates on the buffers 1 and 2
//     //returns match score (matchScore)
//     //eg. mattmp
//     else if(commandString == "mattmp") {
//       response = fps.matchTemplates();
//     }
//     //-------------------------------------------------------------------------//
//     //search the library for content on the buffer
//     //buffer ID should be 1 or 2
//     //start location cane be #1 to #1000 (don't send the "#" with command)
//     //eg. serlib 1 10 50
//     else if(commandString == "serlib") {
//       uint8_t bufferId = firstParam.toInt();
//       uint16_t startLocation = secondParam.toInt();
//       uint16_t count = thirdParam.toInt();
//       response = fps.searchLibrary(bufferId, startLocation, count);
//     }
//     //-------------------------------------------------------------------------//
//     //unknown command
//     else {
//       Serial.print("Invalid command : ");
//       Serial.println(commandString);
//     }
//     Serial.println("...........................");
//     Serial.println();
//     delay(2000);
//   }
// }
// //=========================================================================//









#include<Adafruit_Fingerprint.h>
#include<SoftwareSerial.h>


SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

uint8_t id;

void setup() 
{
  Serial.begin(9600);
  finger.begin(57600);
  if (finger.verifyPassword())
  {
    Serial.println("found fingerprint sensor");
  }
  else
  {
    Serial.println("did not find fingerprint sensor");
    while(1)
    {
      delay(1);
    }
  }
}

uint8_t readnumber(void) {

 uint8_t num = 0;

 while (num == 0) {

   while (! Serial.available());

   num = Serial.parseInt();

 }

 return num;

}

 

void loop()                     // run over and over again

{

 Serial.println("Ready to enroll a fingerprint!");

 Serial.println("Please type in the ID # (from 1 to 127) you want to save this finger as...");

 id = readnumber();

 if (id == 0) {// ID #0 not allowed, try again!

    return;

 }

 Serial.print("Enrolling ID #");

 Serial.println(id);

 

 while (!  getFingerprintEnroll() );

}

 

uint8_t getFingerprintEnroll() {

 

 int p = -1;

 Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);

 while (p != FINGERPRINT_OK) {

   p = finger.getImage();

   switch (p) {

   case FINGERPRINT_OK:

     Serial.println("Image taken");

     break;

   case FINGERPRINT_NOFINGER:

     Serial.println(".");

     break;

   case FINGERPRINT_PACKETRECIEVEERR:

     Serial.println("Communication error");

     break;

   case FINGERPRINT_IMAGEFAIL:

     Serial.println("Imaging error");

     break;

   default:

     Serial.println("Unknown error");

     break;

   }

 }

 

 // OK success!

 

 p = finger.image2Tz(1);

 switch (p) {

   case FINGERPRINT_OK:

     Serial.println("Image converted");

     break;

   case FINGERPRINT_IMAGEMESS:

     Serial.println("Image too messy");

     return p;

   case FINGERPRINT_PACKETRECIEVEERR:

     Serial.println("Communication error");

     return p;

   case FINGERPRINT_FEATUREFAIL:

     Serial.println("Could not find fingerprint features");

     return p;

   case FINGERPRINT_INVALIDIMAGE:

     Serial.println("Could not find fingerprint features");

     return p;

   default:

     Serial.println("Unknown error");

     return p;

 }

 

 Serial.println("Remove finger");

 delay(2000);

 p = 0;

 while (p != FINGERPRINT_NOFINGER) {

   p = finger.getImage();

 }

 Serial.print("ID "); Serial.println(id);

 p = -1;

 Serial.println("Place same finger again");

 while (p != FINGERPRINT_OK) {

   p = finger.getImage();

   switch (p) {

   case FINGERPRINT_OK:

     Serial.println("Image taken");

     break;

   case FINGERPRINT_NOFINGER:

     Serial.print(".");

     break;

   case FINGERPRINT_PACKETRECIEVEERR:

     Serial.println("Communication error");

     break;

   case FINGERPRINT_IMAGEFAIL:

     Serial.println("Imaging error");

     break;

   default:

     Serial.println("Unknown error");

     break;

   }

 }

 

 // OK success!

 

 p = finger.image2Tz(2);

 switch (p) {

   case FINGERPRINT_OK:

     Serial.println("Image converted");

     break;

   case FINGERPRINT_IMAGEMESS:

     Serial.println("Image too messy");

     return p;

   case FINGERPRINT_PACKETRECIEVEERR:

     Serial.println("Communication error");

     return p;

   case FINGERPRINT_FEATUREFAIL:

     Serial.println("Could not find fingerprint features");

     return p;

   case FINGERPRINT_INVALIDIMAGE:

     Serial.println("Could not find fingerprint features");

     return p;

   default:

     Serial.println("Unknown error");

     return p;

 }

 

 // OK converted!

 Serial.print("Creating model for #");  Serial.println(id);

 

 p = finger.createModel();

 if (p == FINGERPRINT_OK) {

   Serial.println("Prints matched!");

 } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

   Serial.println("Communication error");

   return p;

 } else if (p == FINGERPRINT_ENROLLMISMATCH) {

   Serial.println("Fingerprints did not match");

   return p;

 } else {

   Serial.println("Unknown error");

   return p;

 }  

 

 Serial.print("ID "); Serial.println(id);

 p = finger.storeModel(id);

 if (p == FINGERPRINT_OK) {

   Serial.println("Stored!");

 } else if (p == FINGERPRINT_PACKETRECIEVEERR) {

   Serial.println("Communication error");

   return p;

 } else if (p == FINGERPRINT_BADLOCATION) {

   Serial.println("Could not store in that location");

   return p;

 } else if (p == FINGERPRINT_FLASHERR) {

   Serial.println("Error writing to flash");

   return p;

 } else {

   Serial.println("Unknown error");

   return p;

 }  

}
