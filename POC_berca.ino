#include "include.h"

#define INTERVAL 1000

unsigned long prevMillis=0;

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
  notif_powerup();
  mqtt_init();
  mqtt_reconnect();
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long current_millis = millis();
  read_ble();
  delay(10);
  mifare_read();
  delay(10);
  if (current_millis - prevMillis >= INTERVAL){
    prevMillis = current_millis;
    check_beacon();
    notif_network_connected();
    if(!mqtt_loop()){
      notif_network_notconnected();
      mqtt_reconnect();
    }
  }
  
}
