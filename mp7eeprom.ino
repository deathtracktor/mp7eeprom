#include <Wire.h>

#include "hexdump.h"
#include "messages.h"

#define EEPROM_ADDR ( 0x0a << 3 | 0x0)
#define readDelay 30
#define writeDelay 30

static char* toHex(byte b) {
    const char hexdigits[] = "0123456789ABCDEF";
    char res[] = "XX";
    res[0] = hexdigits[(b >> 4) & 0x0F];
    res[1] = hexdigits[b & 0x0F];
    return res;
}

boolean testConnection() {
   int ofs = 0;
   Wire.beginTransmission(EEPROM_ADDR); 
   Wire.write(ofs);
   Wire.endTransmission();
   delay(readDelay); 
   Wire.requestFrom(EEPROM_ADDR, 1);
   return Wire.available();
}

byte readByte(int ofs) {
   Wire.beginTransmission(EEPROM_ADDR); 
   Wire.write(ofs);
   Wire.endTransmission();
   delay(readDelay); 
   Wire.requestFrom(EEPROM_ADDR, 1);
   return Wire.read();
}

void writeByte(byte b, int ofs) {
   Wire.beginTransmission(EEPROM_ADDR);
//   TWAR |= 1; // We need to set the RW bit high to write
   Wire.write(ofs);
   Wire.write(b);
   Wire.endTransmission();
   delay(writeDelay);  
}

// reads current EEPROM data
void testRead() {
   for (int offset = 0; offset <= 255; offset++){
       Serial.print(toHex(readByte(offset)));
       if ((offset & 0x0F) == 0x0F) { Serial.println(); } else { Serial.print('.'); }
   }   
}


// writes a 'clean' EEPROM dump
void writeDump() {
   Serial.println(msgRewritingData);
   for (int offset = 0; offset <= 255; offset++){
       writeByte(dump[offset], offset);
       Serial.print(msgUpdatingAddress);
       Serial.print(toHex(offset));
       Serial.print('\r');
   }
   Serial.println();
   Serial.println(msgFinished);
}

void setup() {
   Wire.begin();
   Serial.begin(9600);
   Serial.println(msgStartup);
   // testing connection
   while (true) {
      while (Serial.read() == -1) {}
      if (testConnection()) { break; } else { Serial.println(msgConnectionFailed); }    
   }
   Serial.println(msgConnectionEstablished);  
}

void loop() {
  
   Serial.println(msgMenu);
   int choice = -1;
   while (choice == -1) { choice = Serial.read(); }
  
   // checking user input
   switch (choice) {
   case '1' :
       // test read EEPROM
       testRead();
       break;
   case '2' :
       // writing the dump
       writeDump();
       break;
   default :
       Serial.println(msgInvalidInput);
   }
}
