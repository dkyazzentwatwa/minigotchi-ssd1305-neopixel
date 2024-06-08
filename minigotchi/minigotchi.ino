/**
 * minigotchi.ino: everything implemented here
*/

#include "config.h"
#include "minigotchi.h"
#include <Adafruit_NeoPixel.h>
#include <Ticker.h>

#define NEOPIXEL_PIN 2
#define NUMPIXELS 1
Adafruit_NeoPixel pixels(NUMPIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
Ticker blinker;

volatile bool isBlinking = false;
volatile uint32_t currentColor = 0;

Config config;
Minigotchi minigotchi;

void setup() {
  Serial.begin(config.baud);
  pixels.begin();
  minigotchi.boot();
}

void blink() {
  static bool state = false;
  if (isBlinking) {
    if (state) {
      pixels.setPixelColor(0, currentColor);
    } else {
      pixels.setPixelColor(0, 0);  // Turn off
    }
    pixels.show();
    state = !state;
  }
}

void startBlinking(uint32_t color) {
  currentColor = color;
  isBlinking = true;
  blinker.attach(0.5, blink);  // Blink every 0.5 seconds
}

void stopBlinking() {
  isBlinking = false;
  blinker.detach();
  pixels.setPixelColor(0, 0);  // Turn off
  pixels.show();
}
/** developer note: 
 *
 * everything should have been moved to minigotchi.cpp
 * as the program becomes more complicated, it gets easier to maintain all the main features in one file
 * 
*/

void loop() {
  // cycle channels at start of loop
  startBlinking(0x0000FF);  // Blue
  minigotchi.cycle();
  delay(1000);
  stopBlinking();

  // the longer we are on this channel, the more likely we're gonna see a pwnagotchi on this channel
  // get local payload from local pwnagotchi, send raw frame if one is found
  startBlinking(0x00FF00);  // Green
  minigotchi.detect();
  delay(1000);
  stopBlinking();


  // advertise our presence with the help of pwngrid compatible beacon frames (probably the most confusing part lmao)
  startBlinking(0xFFFF00);  // Yellow
  minigotchi.advertise();
  delay(1000);
  stopBlinking();

  // deauth random access point
  startBlinking(0xFF0000);  // Red
  minigotchi.deauth();
  delay(1000);
  stopBlinking();
}
