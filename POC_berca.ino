#include "include.h"
#define SERVO_PIN 12
#define INTERVAL 1000

unsigned long prevMillis = 0;

void setup() {
  // put your setup code here, to run once:
  notif_init();
  myservo_init(SERVO_PIN);
  myservo_close();
  notif_powerup();
  Serial.begin(115200);
  delay(100);
  if(!flash_init()){
    Serial.println("An Error has occurred while mounting SPIFFS");
  }
  config_all();
  setup_wifi_ap();
  webserver_start();
  setup_wifi_sta();
  ble_scan_init();
  mifare_init();
  iBeacon_init();
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
