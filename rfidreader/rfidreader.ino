/*******************************************************
Program  : ARDUINO dengan RFID MFRC-522
Chip     : Arduino Uno
********************************************************/

#include <SPI.h> 
#include <MFRC522.h>
#include <ArduinoJson.h>
 
#define SS_PIN 10
#define RST_PIN 9
#define RELAY 8
MFRC522 mfrc522(SS_PIN, RST_PIN); 

long previousMillis_rfid = 0;
long previousMillis_serial = 0;

long interval_read_rfid = 2000;
long interval_read_serial = 10; 

void setup() 
{

  Serial.begin(115200);   
  SPI.begin(); 
  pinMode(RELAY, OUTPUT);     
  mfrc522.PCD_Init();   
  Serial.println("Dekatkan Tag RFID (Dapat berupa kartu atau gantungan kunci) ke RFID reader");
  digitalWrite(RELAY, LOW);
  Serial.println();
  
}
void loop() 
{
  if(Serial.available() > 0)
  {
    int stts = Serial.parseInt();
    if(stts == 1){
      buka_pintu();  
    }
    
  }
  
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  sendUid(content);
  delay(1000);
}

void buka_pintu()
{
  digitalWrite(RELAY, HIGH);
  delay(5000);
  digitalWrite(RELAY, LOW);
}

void sendUid(String ids){
   StaticJsonBuffer<200> jsonBuffer;
   JsonObject& root = jsonBuffer.createObject();
   root["uid"] = ids;
   root.printTo(Serial);
//   Serial.println();
}
