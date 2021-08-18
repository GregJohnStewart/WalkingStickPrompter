/**
 * Log and status LED helpers for the WalkingStick Prompter.
 * Author: Greg Stewart
 * 
 * https://github.com/GregJohnStewart/WalkingStickPrompter
 */
#ifndef STATUS_LOG_HELPERS_H
#define STATUS_LOG_HELPERS_H

#include "Arduino.h"
#include "globals.h"
#include "tftSdModuleHelpers.h"

void turnStatusLightOn(){
  digitalWrite(STATUS_LED, HIGH);
}
void turnStatusLightOff(){
  digitalWrite(STATUS_LED, LOW);
}

void alertStatus(int ind, bool indefinately){
  turnStatusLightOff();
  do {
    for(int i = 0; i < ind; i++){
      turnStatusLightOn();
      delay(ALERT_STATUS_BLINK_ON_DUR);
      turnStatusLightOff();
      delay(ALERT_STATUS_BLINK_OFF_DUR);
    }
    if(indefinately){
      delay(ALERT_STATUS_BLINK_OFF_DUR * 2);
    }
    //Serial.println("alerted");
  } while(indefinately);
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

const char* getTabs(const int numTabs){
  char* tabs = new char[numTabs + 1];

  for(int i = 0; i < numTabs; i++){
    tabs[i] = "\t";
  }
  tabs[numTabs] = "\0";
  
  return tabs;
}

void writeSerial(bool newline, const char* line){
  if(!SERIAL_LOGS_ENABLED){
    return;
  }
  const char* tabs = getTabs(CUR_TAB_LEVEL);
  
  Serial.print(tabs);
  if(newline){
    Serial.println(line);
  } else {
    Serial.print(line);
  }
  delete[] tabs;
}

void writeSerial(const char* line){
  writeSerial(false, line);
}

void writeSerialLine(const char* line){
  writeSerial(true, line);
}

void writeSerial(const __FlashStringHelper * ifsh){
  const char* PROGMEM line = (const char PROGMEM *)ifsh;
  writeSerial(false, line);
}

void writeSerialLine(const __FlashStringHelper * ifsh){
  const char* PROGMEM line = (const char PROGMEM *)ifsh;
  writeSerial(true, line);
}

void writeSerialLine(const int num){
  char s[9];
  snprintf(s, sizeof(s), "%i", num);
  writeSerial(true, s);
}

void writeSerial(int num){
  char s[9];
  snprintf(s, sizeof(s), "%i", num);
  writeSerial(false, s);
}

void outFreeRam(){
  writeSerial(F("Free ram: "));
  writeSerialLine(freeRam());
}

void displaySplashScreen(){
  writeSerialLine(F("Displaying Splash Screen..."));
  CUR_TAB_LEVEL++;
  
  //TFT.fillScreen(ILI9341_BLACK);
  
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(4);
  TFT.println(F("Walking Stick\nPrompter"));
  
  TFT.setTextSize(3);
  TFT.print(F("Version: "));
  
  TFT.setTextColor(ILI9341_YELLOW);
  TFT.println(VERSION);
  
  TFT.setTextColor(ILI9341_WHITE);
  
  TFT.println();
  TFT.setTextSize(1);
  
  TFT.print(F("Serial Logging: "));
  
  if(SERIAL_LOGS_ENABLED){ 
    TFT.setTextColor(ILI9341_GREEN);
    TFT.println("ENABLED");
  } else {
    TFT.println("Off");
  }
  
  TFT.setTextColor(ILI9341_WHITE);
  
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Displaying Splash Screen."));
}

void displayErrMessage(const char* message, const bool hang){
  
  //TFT.fillScreen(ILI9341_BLACK);
  
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_RED);
  TFT.setTextSize(3);
  TFT.println(message);
  
  if(hang){
    while(1);
  }
}


void displayErrMessage(const __FlashStringHelper * message, const bool hang){
  const char* line = (const char PROGMEM *)message;
  displayErrMessage(line, hang);
}


//TODO:: add thing to write to tft notifying of sd activity
//TODO:: add thing to clear sd activity notifier

#endif
