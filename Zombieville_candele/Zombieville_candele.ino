/* ***********************************************
* Zombieville
* 3 candele
* 
* Get library from https://github.com/ljos/MFRC522
* Sketch: gudjonholm@gmail.com
* 
* 
* 
* Pins    SPI        UNO    Mega2560  Leonardo
* 1 (NSS) SDA (SS)   10     53        10
* 2       SCK        13     52        SCK1
* 3       MOSI       11     51        MOSI1
* 4       MISO       12     50        MISO1
* 5       IRQ        *      *         *
* 6       GND        GND     GND       GND
* 7       RST        9      ?         Reset
* 8      +3.3V (VCC) 3V3     3V3       3.3V
************************************************** */

#include <MFRC522.h>
#include <SPI.h>

#define SDA 10
#define RST 9

#define ledPinOpen    3
#define ledPinClosed  4

MFRC522 nfc(SDA, RST);

boolean Opening = true;

void setup() {
  pinMode(ledPinOpen  , OUTPUT);
  pinMode(ledPinClosed, OUTPUT);
  digitalWrite(ledPinOpen, Opening);
  digitalWrite(ledPinClosed, !Opening);
  
  SPI.begin();
  Serial.begin(9600);
  
  while (!Serial) {
  ; // wait for serial port to connect. Needed for Leonardo only
  }
  
  Serial.println("Looking for MFRC522.");
  nfc.begin();
  
  byte version = nfc.getFirmwareVersion();
  if (! version) {
    Serial.print("Didn't find MFRC522 board.");
    while(1); //halt
  }

  Serial.print("Found chip MFRC522 ");
  Serial.print("Firmware ver. 0x");
  Serial.print(version, HEX);
  Serial.println(".");
}

/*If you want more Authorized of cards set the count here, and then add the serials below*/
#define AUTHORIZED_COUNT 1 
/*
 * Numero 1 D5 6E CF 65
 * Numero 1 (ntag) 88 4 9 66 
 * Numero 2 B5 8 1E C3
 * Numero 2 (ntag) 88 4 F5 66
 * Numero 3 9D AF 9F 59
 * Numero 3 (ntag) 88 4 A 66
 */
byte Authorized[AUTHORIZED_COUNT][4] = {
  {0x88, 0x4, 0xF5, 0x66, }
  //,{0x10, 0x14, 0x39, 0x2E, 0xFF, 0xFF, }  //example how to add more authorized cards
  };
                          
void printSerial(byte *serial);
boolean isSame(byte *key, byte *serial);
boolean isAuthorized(byte *serial);

void loop() {
  byte status;
  byte data[MAX_LEN];
  byte serial[5];
  
  // Send a general request out into the aether. If there is a tag in
  // the area it will respond and the status will be MI_OK.
  status = nfc.requestTag(MF1_REQIDL, data);

  if (status == MI_OK) {
    status = nfc.antiCollision(data);
    memcpy(serial, data, 5);
    
    if(isAuthorized(serial))
    { 
      Serial.println("Authenticated");
      //Opening = !Opening; // Interruttore ON-OFF
      Opening = false;   // Apertura relay temporizzata abilita Opening nel loop
    }
    else
    { 
      printSerial(serial);
      Serial.println("is NOT authenticated");
      Opening = true;
    }
    
    nfc.haltTag();
    digitalWrite(ledPinOpen, Opening);
    digitalWrite(ledPinClosed, !Opening);
    delay(2000);
  }
  delay(500);
}


boolean isSame(byte *key, byte *serial)
{
    for (int i = 0; i < 4; i++)
    {
      if (key[i] != serial[i])
      { 
        return false; 
      }
    }
    return true;
}

boolean isAuthorized(byte *serial)
{
    for(int i = 0; i < AUTHORIZED_COUNT; i++)
    {
      if(isSame(serial, Authorized[i]))
      return true;
    }
    return false;
}

void printSerial(byte *serial)
{
    Serial.print("Serial:");
    for (int i = 0; i < 4; i++) {
    Serial.print(serial[i], HEX);
    Serial.print(" ");
    }
}
