#include <WiFi.h>

void setup_wifi() {
  WiFi.mode(WIFI_AP_STA); 
  WiFi.softAP(ap_ssid,ap_passwrd);
  Serial.print("AP mode on ");
  Serial.println(WiFi.softAPIP());
  delay(1000);
  Serial.print("Connecting to ");
  Serial.println(sta_ssid);

  WiFi.begin(sta_ssid, sta_passwrd);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  
}
