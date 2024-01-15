#include <SPI.h>
//#include <deprecated.h>
#include <MFRC522.h>
//#include <MFRC522Extended.h>
//#include <require_cpp11.h>
#define sda 53
#define rst 5
MFRC522 mfrc522(sda,rst);

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
SPI.begin();
mfrc522.PCD_Init();
Serial.println("touch the card on the reader");
Serial.println();
pinMode(10,OUTPUT);
pinMode(11,OUTPUT);
digitalWrite(11,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
// Look for new cards
  digitalWrite(11,HIGH);
  digitalWrite(10,LOW);
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  content.toUpperCase();
  if (content.substring(1)== "A3 2C 40 05")
  {
    digitalWrite(10,HIGH);
    digitalWrite(11, LOW);
    delay(1000);
  }
  else
  {
     digitalWrite(11,HIGH);
    digitalWrite(10, LOW);
    delay(1000);
    }
  }
