#include "include.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(100);
  ble_scan_init();
  mifare_init();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  read_ble();
  delay(10);
  mifare_read();
  delay(10);
  
}
