/**
 * pwnagotchi.h: header files for pwnagotchi.cpp
*/

#ifndef PWNAGOTCHI_H
#define PWNAGOTCHI_H

#include "frame.h"
#include "minigotchi.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <stdint.h>
#include <string>

extern "C" {
    #include "structs.h"
}

class Pwnagotchi {
public:
    static void detect();
    static void pwnagotchiCallback(unsigned char *buf, short unsigned int type);
    static void stopCallback();

private:
    static std::string extractMAC(const unsigned char *buff);
    static void getMAC(char* addr, const unsigned char* buff, int offset);
    static std::string essid;
    static bool pwnagotchiDetected;
};

#endif // PWNAGOTCHI_H
