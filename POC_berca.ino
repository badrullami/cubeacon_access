#include "include.h"

extern void notif_cardpresent();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  if(!flash_init()){
    Serial.println("An Error has occurred while mounting SPIFFS");
  }
  config_all();
  setup_wifi();
  ble_scan_init();
  mifare_init();
  notif_init();
  notif_cardpresent();
}

void loop() {
  // put your main code here, to run repeatedly:
  read_ble();
  delay(10);
  mifare_read();
  delay(10);
}
