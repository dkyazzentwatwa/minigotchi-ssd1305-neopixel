/////////////////////////////////////////
// webui.h: header files for webui.cpp //
/////////////////////////////////////////

#ifndef WEBUI_H
#define WEBUI_H

// add esp-fs-webserver library here
// this will handle wifi and file editing plus or minus the webui
#include <ESPAsyncWebServer.h>
#include <FS.h> 
#include <ESP8266WiFi.h>

class WebUI {
public:
    WebUI();
    void setupWebServer();

private:
    const char* apName;
    const char* apPassword; 
    const char* hostname;
    void handleRoot();
};

#endif // WEBUI_H
