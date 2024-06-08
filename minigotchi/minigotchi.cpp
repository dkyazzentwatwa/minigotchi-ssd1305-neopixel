/**
 * minigotchi.cpp: handles system usage info, etc
*/

#include "minigotchi.h"

// 'ANGRY', 75x75px

/** developer note:
 *
 * the functions here provide info on the minigotchi, such as memory, temperature, etc.
 * all this really does is print information to the serial terminal
 * this is meant to be ran on startup.
 *
*/

// this code is pretty disgusting and shitty but it makes minigotchi.ino less cluttered!!!

// things to do when starting up
void Minigotchi::boot() {
    Display::startScreen();
    Serial.println(" ");
    Serial.println("(^-^) hi..i'm Minigotchi..ur pwnagotchi's bst-frnd!");
    Display::cleanDisplayFace("(v_v)");
    Display::attachSmallText("hi..i'm minigotchi");
    Serial.println(" ");
    Serial.println("('-') You can edit my configuration parameters in config.cpp!");
    Serial.println(" ");
    delay(1000);
    Display::cleanDisplayFace("(a_a)");
    Display::attachSmallText("edit config.cpp..");
    delay(1000);
    Serial.println("(>-<) Starting now...");
    Serial.println(" ");
    Display::cleanDisplayFace("(w_w)");
    Display::attachSmallText("startin now");
    delay(1000);
    Serial.println("################################################");
    Serial.println("#                BOOTUP PROCESS                #");
    Serial.println("################################################");
    Serial.println(" ");
    Deauth::list();
    Channel::init(Config::channel);
    Minigotchi::info();
    Minigotchi::finish();
}

void Minigotchi::info() {
    delay(1000);
    Serial.println(" ");
    Serial.println("('-') Current Minigotchi Stats: ");
    Display::cleanDisplayFace("(a_a)");
    Display::attachSmallText("current stats:");
    version();
    mem();
    cpu();
    Serial.println(" ");
    delay(1000);
}

// if this can be printed, everything should have gone right...
void Minigotchi::finish() {
    Serial.println("################################################");
    Serial.println(" ");
    Serial.println("('-') Started successfully!");
    Serial.println(" ");
    Display::cleanDisplayFace("(m_m)");
    Display::attachSmallText("started sucessfully");
    delay(1000);
}

void Minigotchi::version() {
    Serial.print("('-') Version: ");
    Serial.println(Config::version.c_str());
    Display::cleanDisplayFace("(m_M)");
    Display::attachSmallText("ver: " + (String) Config::version.c_str());
    delay(1000);
}

void Minigotchi::mem() {
    Serial.print("('-') Heap: ");
    Serial.print(ESP.getFreeHeap());
    Serial.println(" bytes");
    Display::cleanDisplayFace("(M_m)");
    Display::attachSmallText("heap: " + (String) ESP.getFreeHeap() + " bytes");
    delay(1000);
}

void Minigotchi::cpu() {
    Serial.print("('-') CPU Frequency: ");
    Serial.print(ESP.getCpuFreqMHz());
    Serial.println(" MHz");
    Display::cleanDisplayFace("(m_M)");
    Display::attachSmallText("CPU freq: " + (String) ESP.getCpuFreqMHz() + " MHz");
    delay(1000);
}

/** developer note:
 *
 * these functions are much like the pwnagotchi's monstart and monstop which start and stop monitor mode. neat!
 *
 * obviously i like to keep things consistent with the pwnagotchi, this is one of those things.
 *
*/

/** developer note:
 *
 * to prevent issues we put the minigotchi back into client mode which is the "default"
 *
*/

void Minigotchi::monStart() {
    // disconnect from WiFi if we were at all
    WiFi.disconnect();

    // revert to station mode
    wifi_set_opmode(STATION_MODE);
    wifi_promiscuous_enable(1);
}

void Minigotchi::monStop() {
    wifi_promiscuous_enable(0);

    // revert to station mode
    wifi_set_opmode(STATION_MODE);
}

/** developer note:
 *
 * when the minigotchi isn't cycling, detecting a pwnagotchi, or deauthing,
 * it is advertising it's own presence, hence the reason there being a constant
 * Frame::stop(); and Frame::start(); in each function
 *
 * when it comes to any of these features, you can't just call something and expect it to run normally
 * ex: calling Deauth::deauth();
 * because you're gonna get the error:
 *
 * (X-X) No access point selected. Use select() first.
 * ('-') Told you so!
 *
 * the card is still busy in monitor mode on a certain channel(advertising), and the AP's we're looking for could be on other channels
 * hence we need to call Frame::stop(); to stop this then we can do what we want...
 *
*/

// channel cycling
void Minigotchi::cycle() {
    Channel::cycle();
}

// pwnagotchi detection
void Minigotchi::detect() {
    Pwnagotchi::detect();
}

// deauthing
void Minigotchi::deauth() {
    Deauth::deauth();
}

// advertising
void Minigotchi::advertise() {
    Frame::advertise();
}