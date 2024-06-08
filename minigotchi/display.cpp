/**
 * display.cpp: handles display support
*/

#include "display.h"

Adafruit_SSD1305* adafruit_display;

void Display::startScreen() {
  adafruit_display = new Adafruit_SSD1305(128, 32, &SPI, OLED_DC, OLED_RESET, OLED_CS, 7000000UL);
  adafruit_display->begin(SSD1305_I2C_ADDRESS, 0x3c);  // initialize with the I2C addr 0x3C (for the 64x48)
  delay(10);
  // initialize w/ delays to prevent crash
  adafruit_display->display();
  delay(10);
  adafruit_display->clearDisplay();
  delay(10);
  adafruit_display->setTextColor(WHITE);
  delay(10);
}

void Display::cleanDisplayFace(String text) {
  if (Config::display) {
    adafruit_display->setCursor(32, 0);
    delay(5);
    adafruit_display->setTextSize(2);
    delay(5);
    adafruit_display->clearDisplay();
    delay(5);
    adafruit_display->println(text);
    delay(5);
    adafruit_display->display();
    delay(5);
  }
}

void Display::attachSmallText(String text) {
  if (Config::display) {
    adafruit_display->setCursor(0, 15);
    delay(5);
    adafruit_display->setTextSize(1);
    delay(5);
    adafruit_display->println(text);
    delay(5);
    adafruit_display->display();
    delay(5);
  }
}
