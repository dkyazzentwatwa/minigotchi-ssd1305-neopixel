/**
 * display.h: header files for display.cpp
 */

#ifndef DISPLAY_H
#define DISPLAY_H

#include "config.h"
#include <Adafruit_GFX.h>
//added SSD1305 screens
#include <Adafruit_SSD1305.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

//added 128x32 screens
// SSD1305 screen
#define SSD1305_SCREEN_WIDTH 128
#define SSD1305_SCREEN_HEIGHT 32

// SSD1306 screen
#define SSD1306_SCREEN_HEIGHT 64
#define SSD1306_SCREEN_WIDTH 128

// Init screen
#define SSD1306_OLED_RESET -1
#define SSD1305_OLED_RESET -1
#define WEMOS_OLED_SHIELD_OLED_RESET 0  // GPIO0
#define OLED_CLK 14                     // GPIO 14 (D5)
#define OLED_MOSI 13                    // GPIO 13 (D7)

// Used for software or hardware SPI
#define OLED_CS 15  // GPIO 15 (D8)
#define OLED_DC 4   // GPIO 4 (D2)

// Used for I2C or SPI
#define OLED_RESET 5  // GPIO 5 (SCL)

class Display {
public:
  static void startScreen();
  static void cleanDisplayFace(String text);
  static void attachSmallText(String text);
};

#endif  // DISPLAY_H
