/**
 * channel.cpp: handles channel switching
*/

#include "channel.h"

/** developer note:
 *
 * i am using the ideal 2.4 GHz channels, which are 1, 6, and 11.
 * the reason for that is so we don't interfere with other devices on our frequency.
 * there are probably plenty more reasons but this is a good practice for such iot devices.
 *
 */

// same channels in config
int Channel::channelList[13] = {
  Config::channels[0], Config::channels[1], Config::channels[2], Config::channels[3],
  Config::channels[4], Config::channels[5], Config::channels[6], Config::channels[7],
  Config::channels[8], Config::channels[9], Config::channels[10], Config::channels[11],
  Config::channels[12]
};

void Channel::init(int initChannel) {
  // start on user specified channel
  delay(1000);
  Serial.println(" ");
  Serial.print("(-.-) Initializing on channel ");
  Serial.println(initChannel);
  Serial.println(" ");
  Display::cleanDisplayFace("(O_o)");
  Display::attachSmallText("init. on ch. " + (String)initChannel);
  delay(1000);

  // switch channel
  Minigotchi::monStop();
  wifi_set_channel(initChannel);
  Minigotchi::monStart();

  if (initChannel == getChannel()) {
    Serial.print("('-') Successfully initialized on channel ");
    Serial.println(getChannel());
    Display::cleanDisplayFace("(U_u)>");
    Display::attachSmallText("Successfully init on ch. " + (String)getChannel());
    delay(1000);
  } else {
    Serial.print("(X-X) Channel initialization failed, try again?");
    Display::cleanDisplayFace("(x_X;)");
    Display::attachSmallText("Ch. init failed, try again?");
    delay(1000);
  }
}

void Channel::cycle() {
  // get channels
  int numChannels = sizeof(channelList) / sizeof(channelList[0]);

  // select a random one
  int randomIndex = random(numChannels);
  int newChannel = channelList[randomIndex];

  // switch here
  switchChannel(newChannel);
}

void Channel::switchChannel(int newChannel) {
  // switch to channel
  delay(1000);
  Serial.print("(-.-) Switching to channel ");
  Serial.println(newChannel);
  Serial.println(" ");
  Display::cleanDisplayFace("(u_U)");
  Display::attachSmallText("switching to ch. " + (String)newChannel);
  delay(1000);

  // monitor this one channel
  Minigotchi::monStop();
  wifi_set_channel(newChannel);
  Minigotchi::monStart();

  // switched channel
  checkChannel(newChannel);
}

// check if the channel switch was successful
void Channel::checkChannel(int channel) {
  if (channel == getChannel()) {
    Serial.print("('-') Currently on channel ");
    Serial.println(getChannel());
    Display::cleanDisplayFace("(>_>)");
    Display::attachSmallText("now on channel " + (String)getChannel());
    Serial.println(" ");
    delay(1000);
  } else {
    Serial.print("(X-X) Channel switch to channel ");
    Serial.print(channel);
    Serial.println(" has failed");
    Serial.print("(X-X) Currently on channel ");
    Serial.print(getChannel());
    Serial.println(" instead");
    Serial.println(" ");
    Display::cleanDisplayFace("(x_X)");
    Display::attachSmallText("ch. switch to " + (String)channel + " has failed");
    delay(1000);
  }
}

int Channel::getChannel() {
  return wifi_get_channel();
}

int Channel::list() {
  return channelList[3];
}
