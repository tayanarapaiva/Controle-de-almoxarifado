#include <MFRC522.h>
#include <SPI.h>
#include <Wire.h>

#define Pin_SDA 10
#define Pin_Reset 9

String leitura, pacote = "";
byte caractere;

MFRC522 RFID (Pin_SDA, Pin_Reset);

void setup() {
  Wire.begin();
  Serial.begin(115200);
  SPI.begin();
  RFID.PCD_Init(); 
}

void loop() {
  leitura = "";
  if (!RFID.PICC_IsNewCardPresent() or !RFID.PICC_ReadCardSerial()){
    return;
  }
  for (byte i=0; i<RFID.uid.size; i++){
    leitura +=
    (RFID.uid.uidByte[i] < 0x10 ? "0" : "") +
    String(RFID.uid.uidByte[i], HEX) +
    (i!=3 ? ":" : "");
  }
  leitura.toUpperCase();
  Serial.print("{"+leitura+"}");
  delay(1000);
  
}
