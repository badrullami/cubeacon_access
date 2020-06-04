#include <ESPAsyncWebServer.h>
#include "index_html.h"

AsyncWebServer myserver(80);

//function prototype


String processor(const String& var){
  return String();
}

void webserver_start(){
  myserver.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
    });
  myserver.on("/config", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/html", "Setting parameter success, please return home page and reboot soon! <br><a href=\"/\">Return to Home Page</a>");
    });
    
  myserver.begin();
}
