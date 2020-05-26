#include <SPIFFS.h>
#include <ArduinoJson.h>

#define CONF_STA_FILE "/conf_sta.json"
#define CONF_AP_FILE "/conf_ap.json"

double proximity = 1.0;
String master_key = "eyrodigitallabs\0"; 

const char* sta_ssid = "";
const char* sta_passwrd = "";

const char* ap_ssid = "";
const char* ap_passwrd = "";

String json = "";
DynamicJsonDocument doc(200);

bool flash_init(){
  if(SPIFFS.begin(true)){
    return true;
  }
  else{
    return false;
  }
}

String open_spiff(String file_name){
  json = "";
  File file = SPIFFS.open(file_name);

  if(!file){
    Serial.println("Failed to open file for reading");
    return "";
  }
  Serial.println("File Content:");
 
  while(file.available()){
    json += (char)file.read();
  }
  file.close();
  delay(100);
  return json;
}

void write_spiff(String file_name, String json){
  File file = SPIFFS.open(file_name, FILE_WRITE);
 
    if(!file){
        Serial.println("There was an error opening the file for writing");
        return;
    }
 
    if(file.print(json)){
        Serial.println("File was written");
    } else {
        Serial.println("File write failed");
    }
 
    file.close();
}

void set_sta(const char* ssid, const char* passwrd){
  sta_ssid = ssid;
  sta_passwrd = passwrd;
  String raw_json = open_spiff(CONF_STA_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  doc["sta_ssid"] = ssid;
  doc["sta_passwrd"] = passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_STA_FILE,raw_json);
}

void set_ap(const char* ssid, const char* passwrd){
  ap_ssid = ssid;
  ap_passwrd = passwrd;
  String raw_json = open_spiff(CONF_AP_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  doc["ap_ssid"] = ssid;
  doc["ap_passwrd"] = passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_AP_FILE,raw_json);
}
void read_sta_conf(){
  String raw_json = open_spiff(CONF_STA_FILE);
  deserializeJson(doc,raw_json);
  sta_ssid = doc["sta_ssid"];
  Serial.println(sta_ssid);
  sta_passwrd = doc["sta_passwrd"];
  Serial.println(sta_passwrd);
}

void read_ap_conf(){
  String raw_json = open_spiff(CONF_AP_FILE);
  deserializeJson(doc,raw_json);
  ap_ssid = doc["ap_ssid"];
  Serial.println(ap_ssid);
  ap_passwrd = doc["ap_passwrd"];
  Serial.println(ap_passwrd);
}

void config_all(){
  read_ap_conf();
  read_sta_conf();
}
