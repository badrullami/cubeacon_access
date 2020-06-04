#include <PubSubClient.h>
#include <ArduinoJson.h>

#define TOKEN_LENGTH 6
#define PUBS_TOPIC  dev_type() + "rs/" + dev_id()
#define HB_TOPIC    dev_type() + "hb/" + dev_id()
#define DATA_TOPIC  dev_type() + "rc/" + dev_id()
#define HEAD_TOPIC  dev_type() + dev_id()
#define SUBS_TOPIC  dev_type() + dev_id() + "/#"

WiFiClient espClient;
PubSubClient client(espClient);

//function_prototype
void mqtt_init();
void mqtt_callback(char* topic, byte* payload, unsigned int len);
void handle_newbeacon(String value);

String backend_server = "";
String backend_username = "";
String backend_passwrd = "";
String subs_topic = SUBS_TOPIC;
String pubs_topic = PUBS_TOPIC;
uint16_t backend_port = 0;

void mqtt_init(){
  Serial.print("connecting to: ");
  Serial.print(backend_server);
  Serial.print(backend_port);
  Serial.println(backend_username);
  client.setServer(backend_server.c_str(), backend_port);
  client.setCallback(mqtt_callback);
}

void mqtt_callback(char* topic, byte* payload, unsigned int len){
  String topic_s = topic;
  String subtopic = topic_s.substring(10);
  Serial.println(subtopic);
  
  String payload_s = (char*)payload;
  payload_s = payload_s.substring(0,len);
  
  String pub = PUBS_TOPIC;
 
  if(topic_s.substring(0,9) == HEAD_TOPIC){
    String ret_token = parse_string(payload_s,'&',1);
    if(ret_token.length() == TOKEN_LENGTH){
      String value = parse_string(payload_s,'&',0);
      if(subtopic == "opengate"){
       myservo_open();
       delay(4000);
       myservo_close();
      }
    }
  }  
}

void mqtt_reconnect(){
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect

    String dev_code = dev_type();
    if (client.connect(dev_code.c_str(), backend_username.c_str(), backend_passwrd.c_str())) {
      Serial.println("connected");
      // Subscribe
      Serial.println("subs topic: " + subs_topic);
      client.subscribe(subs_topic.c_str());
    } 
    else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

boolean mqtt_loop(){
  return client.loop();
}

void mqtt_publish(String topic, String payload){
  client.publish(topic.c_str(),payload.c_str());
  Serial.println("publish data :" + topic + " " + payload);
}

void handle_newbeacon(String value){
  uint16_t major = parse_string(value,',',0).toInt();
  uint16_t minor = parse_string(value,',',1).toInt();
  String raw_uuid = parse_string(value,',',2);
  String uuid = "";
  iBeacon_stop();
  aes_encrypt(raw_uuid,uuid);
  iBeacon_set(major,minor,1000,uuid);
  iBeacon_start();
}

void append_beacon(String lastdigit_uuid, uint16_t major, uint16_t minor){
  String payload = lastdigit_uuid + (String)major +(String)minor;
  DynamicJsonDocument json_doc(30);
  json_doc["beacon"] = payload;
  String pub_data;
  serializeJson(json_doc,pub_data);
  mqtt_publish(pubs_topic,pub_data);
}

void append_mifare(String uid){
  String payload = "";
  DynamicJsonDocument json_doc(30);
  json_doc["mifare"] = uid;
  String pub_data;
  serializeJson(json_doc,pub_data);
  mqtt_publish(pubs_topic,pub_data);
}
