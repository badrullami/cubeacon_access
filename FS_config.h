#include <SPIFFS.h>
#include <ArduinoJson.h>

#define CONF_STA_FILE "/conf_sta.json"
#define CONF_AP_FILE "/conf_ap.json"
#define CONF_BACKEND_FILE "/conf_mqtt.json"

String json = "";
const char* json_value = "";
DynamicJsonDocument doc(300);

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
  deserializeJson(doc,raw_json);
  doc["sta_ssid"] = sta_ssid;
  doc["sta_passwrd"] = sta_passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_STA_FILE,raw_json);
}

void set_ap(const char* ssid, const char* passwrd){
  ap_ssid = ssid;
  ap_passwrd = passwrd;
  String raw_json = open_spiff(CONF_AP_FILE);
  deserializeJson(doc,raw_json);
  doc["ap_ssid"] = ssid;
  doc["ap_passwrd"] = passwrd;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_AP_FILE,raw_json);
}

void set_backend(const char* backend_server, const char* username, const char* passwrd, uint16_t port, const char* subs){
  backend_server = backend_server;
  backend_username = username;
  backend_passwrd = passwrd;
  backend_port = port;
  subs_topic = subs;
  String raw_json = open_spiff(CONF_BACKEND_FILE);
  deserializeJson(doc,raw_json);
  doc["backend_server"] = backend_server;
  doc["backend_user"] = username;
  doc["backend_passwrd"] = passwrd;
  doc["backend_port"] = backend_port;
  doc["subs_topic"] = subs_topic;
  raw_json = "";
  serializeJson(doc,raw_json);
  write_spiff(CONF_BACKEND_FILE,raw_json);
}

void read_sta_conf(){
  String raw_json = open_spiff(CONF_STA_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["sta_ssid"];
  sta_ssid = json_value;
  Serial.println(sta_ssid);
  json_value = doc["sta_passwrd"];
  sta_passwrd = json_value;
  Serial.println(sta_passwrd);
}

void read_ap_conf(){
  String raw_json = open_spiff(CONF_AP_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["ap_ssid"];
  ap_ssid = json_value;
  Serial.println(ap_ssid);
  json_value = doc["ap_passwrd"];
  ap_passwrd = json_value;
  Serial.println(ap_passwrd);
}

void read_backend_conf(){
  String raw_json = open_spiff(CONF_BACKEND_FILE);
  Serial.println(raw_json);
  deserializeJson(doc,raw_json);
  json_value = doc["backend_server"];
  backend_server = json_value;
  Serial.println(backend_server);
  json_value = doc["backend_user"];
  backend_username = json_value;
  Serial.println(backend_username);
  json_value = doc["backend_passwrd"];
  backend_passwrd = json_value;
  Serial.println(backend_passwrd);
  backend_port = doc["backend_port"];
  Serial.println(backend_port);
  json_value = doc["subs_topic"];
  subs_topic =json_value;
  Serial.println(subs_topic);
}


void config_all(){
  read_backend_conf(); delay(500);
  read_sta_conf(); delay(500);
  read_ap_conf(); delay(500);
}
