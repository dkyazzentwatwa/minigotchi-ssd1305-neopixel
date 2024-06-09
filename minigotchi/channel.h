/**
 * channel.h: header files for channel.cpp
*/

#ifndef CHANNEL_H
#define CHANNEL_H

#include "minigotchi.h"
#include "config.h"
#include <ESP8266WiFi.h>

class Channel {
public:
  static void init(int initChannel);
  static void cycle();
  static void switchChannel(int newChannel);
  static int getChannel();
  static void checkChannel(int channel);
  static int list();
  static int channelList[13];  // 13 channels
  static bool isValidChannel(int chn);

private:
  static int randomIndex;
  static int numChannels;
  static int currentChannel;
  static int newChannel;
};

#endif  // CHANNEL_H
