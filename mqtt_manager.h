#include <PubSubClient.h>

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
  String subtopic = topic_s.substring(15);
  
  String payload_s = (char*)payload;
  payload_s = payload_s.substring(0,len);

  Serial.println("receive message");
  iBeacon_stop();
}

void mqtt_reconnect(){
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("barrier_client")) {
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
