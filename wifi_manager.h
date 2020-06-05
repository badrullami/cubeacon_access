String sta_ssid = "";
String sta_passwrd = "";

String ap_ssid = "";
String ap_passwrd = "";

void setup_wifi_ap(){
  WiFi.disconnect();
  WiFi.mode(WIFI_STA); 
  WiFi.softAP(ap_ssid.c_str(),ap_passwrd.c_str());
  Serial.print("AP mode on ");
  Serial.println(WiFi.softAPIP());
  delay(1000); 
}

void setup_wifi_sta(){
  Serial.print("Connecting to ");
  Serial.println(sta_ssid);

  WiFi.begin(sta_ssid.c_str(), sta_passwrd.c_str());
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
