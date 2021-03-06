#include <MFRC522.h>

#define INTERVAL 1000

#define RST_PIN    22          // Configurable, see typical pin layout above
#define SS_PIN     21         // Configurable, see typical pin layout above

unsigned long previousMillis = 0;
uint8_t block = 2;
String master_key = ""; 

MFRC522 mfrc522(SS_PIN, RST_PIN);

//function_prototype
extern void notif_accessgrant();
extern void notif_accessreject();

void mifare_init();
void mifare_read();
String read_rfid();
int readBlock(int blockNumber, byte arrayAddress[]);

void mifare_init(){
  SPI.begin();
  mfrc522.PCD_Init();
  delay(100);  
  mfrc522.PCD_DumpVersionToSerial();
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks...")); 
}

void mifare_read(){
    unsigned long current_millis = millis();
    if (current_millis - previousMillis >= INTERVAL){
      previousMillis = current_millis; 
    
      byte readbackblock[18];
       
      String rfid = read_rfid();
      mfrc522.PCD_StopCrypto1();
    
      if(rfid.length())
      {
        Serial.println("rfid_tag: " + rfid);
        readBlock(block, readbackblock);
        Serial.println(master_key);
        Serial.print("read block: ");
        String key_access = "";
        for (int j=0 ; j<15 ; j++)
        {
          key_access += (char)readbackblock[j];
        }
        Serial.println(key_access);
        mfrc522.PICC_HaltA();
        delay(1000);
        if(key_access == master_key){
          Serial.println("Access granted!");
          notif_accessgrant();
          append_mifare(rfid);
        }
        else{
          Serial.println("Access rejected!");
          notif_accessreject();
       }
     }
   }
}

String read_rfid(){
  String content = "";
  byte letter;

  if (  mfrc522.PICC_IsNewCardPresent())
  {
    if (  mfrc522.PICC_ReadCardSerial())
    {
      for (byte i = 0; i < mfrc522.uid.size; i++)
      {
        content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
        content.concat(String(mfrc522.uid.uidByte[i], HEX));
      }
      
      content.toUpperCase();    
      Serial.println("found mifare card!");
    }
  }
  return content;
}

int readBlock(int blockNumber, byte arrayAddress[]){
  int largestModulo4Number=blockNumber/4*4;
  int trailerBlock=largestModulo4Number+3;//determine trailer block for the sector
  
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;
  
  MFRC522::StatusCode status;
  //authentication of the desired block for access
  status = (MFRC522::StatusCode)mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, trailerBlock, &key, &(mfrc522.uid));
  if (status != MFRC522::STATUS_OK) {
         Serial.print("PCD_Authenticate() failed (read): ");
         Serial.println(mfrc522.GetStatusCodeName(status));
         return 3;//return "3" as error message
  }

//reading a block
byte buffersize = 18;//we need to define a variable with the read buffer size, since the MIFARE_Read method below needs a pointer to the variable that contains the size... 
status = (MFRC522::StatusCode)mfrc522.MIFARE_Read(blockNumber, arrayAddress, &buffersize);//&buffersize is a pointer to the buffersize variable; MIFARE_Read requires a pointer instead of just a number
  if (status != MFRC522::STATUS_OK) {
          Serial.print("MIFARE_read() failed: ");
          Serial.println(mfrc522.GetStatusCodeName(status));
          return 4;//return "4" as error message
  }
  Serial.println("block was read");
}
