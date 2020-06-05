#include <ESPAsyncWebServer.h>
#include "index_html.h"

AsyncWebServer myserver(80);

//function prototype


String processor(const String& var){
  if(var == "STA_SSID"){
    return sta_ssid.c_str();
  }
  else if(var == "STA_PASSWORD"){
    return sta_passwrd.c_str();
  }
  else if(var == "AP_SSID"){
    return ap_ssid.c_str();
  }
  else if(var == "AP_PASSWORD"){
    return ap_passwrd.c_str();
  }
  else if(var == "MQTT_BROKER"){
    return backend_server.c_str();
  }
  else if(var == "MQTT_USERNAME"){
    return backend_username.c_str();
  }
  else if(var == "MQTT_PASSWORD"){
    return backend_passwrd.c_str();
  }
  else if(var == "MQTT_PORT"){
    return (String)backend_port;
  }
  else if(var == "PROXIMITY"){
    return (String)proximity;
  }
  else if(var == "BLE_TIMEOUT"){
    return (String)ble_timeout;
  }
  else if(var == "DETECT_COUNTER"){
    return (String)detect_counter;
  }
  else if(var == "MASTER_KEY"){
    return master_key.c_str();
  }
  return String();
}

static void set_network_sta(AsyncWebServerRequest *request){
  if(request->arg("ssid") != NULL && request->arg("password") != NULL){
    sta_ssid = request->arg("ssid");
    sta_passwrd = request->arg("password");
    set_sta(sta_ssid.c_str(),sta_passwrd.c_str());
    request->send(200, "text/html", "Setting station network success, please return home page and reboot soon! <br><a href=\"/\">Return to Home Page</a>");
  }
  else{
    request->send(200, "text/html", "please enter SSID & Password completely");
  }
}

static void set_network_ap(AsyncWebServerRequest *request){
  if(request->arg("ssid") != NULL && request->arg("password") != NULL){
    ap_ssid = request->arg("ssid");
    ap_passwrd = request->arg("password");
    set_ap(ap_ssid.c_str(),ap_passwrd.c_str());
    request->send(200, "text/html", "Setting access point network success, please return home page and reboot soon! <br><a href=\"/\">Return to Home Page</a>");
  }
  else{
    request->send(200, "text/html", "please enter SSID & Password completely");
  }
}

static void set_backendserver(AsyncWebServerRequest *request){
  if(request->arg("mqtt_broker")&& request->arg("mqtt_username")&& request->arg("mqtt_password")&& request->arg("mqtt_port")){
    backend_server = request->arg("mqtt_broker");
    backend_username = request->arg("mqtt_username");
    backend_passwrd = request->arg("mqtt_password");
    backend_port = request->arg("mqtt_port").toInt();
    set_backend(backend_server.c_str(), backend_username.c_str(), backend_passwrd.c_str(), backend_port);
    request->send(200, "text/html", "Setting Backend success, please return home page and reboot soon! <br><a href=\"/\">Return to Home Page</a>");
  }
  else{
    request->send(200, "text/html", "please enter SSID & Password completely");
  }
}

static void root(AsyncWebServerRequest *request){
  request->send_P(200, "text/html", index_html, processor);
}

static void reboot(AsyncWebServerRequest *request){
  request->send(200, "text/html", "Hardware reboot, please wait for a while and reconnect again!");
}

void webserver_start(){
  myserver.on("/", HTTP_GET, root);
  myserver.on("/config/network_sta", HTTP_POST,set_network_sta);
  myserver.on("/config/network_ap", HTTP_POST,set_network_ap); 
  myserver.on("/config/backend", HTTP_POST,set_backendserver); 
  myserver.on("/reboot", HTTP_POST,reboot);
  myserver.begin();
}
