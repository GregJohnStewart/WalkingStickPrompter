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

void turnStatusLightOn(){
  digitalWrite(STATUS_LED, HIGH);
}
void turnStatusLightOff(){
  digitalWrite(STATUS_LED, LOW);
}

int freeRam () {
  extern int __heap_start, *__brkval; 
  int v; 
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval); 
}

void printTabs(){
  for (byte i=0; i< CUR_TAB_LEVEL; i++) Serial.print(F("\t"));
}

void writeSerial(bool newline, bool doPrintTabs, const char* line){
  if(!SERIAL_LOGS_ENABLED){
    return;
  }
  
  if(doPrintTabs){
    printTabs();
  }
  if(newline){
    Serial.println(line);
  } else {
    Serial.print(line);
  }
}

void writeSerial(bool newline, bool doPrintTabs, const __FlashStringHelper * line){
  if(!SERIAL_LOGS_ENABLED){
    return;
  }
  
  if(doPrintTabs){
    printTabs();
  }
  if(newline){
    Serial.println(line);
  } else {
    Serial.print(line);
  }
}

void writeSerial(const char* line){
  writeSerial(false, true, line);
}

void writeSerialLine(const char* line){
  writeSerial(true, true, line);
}

void writeSerial(const __FlashStringHelper * ifsh){
  writeSerial(false, true, ifsh);
}

void writeSerialLine(const __FlashStringHelper * ifsh){
  writeSerial(true, true, ifsh);
}

void writeSerialLine(const int num){
  char s[9];
  snprintf(s, sizeof(s), "%i", num);
  writeSerial(true, false, s);
}


void writeSerial(int num){
  char s[9];
  snprintf(s, sizeof(s), "%i", num);
  writeSerial(false, false, s);
}

void outFreeRam(){
  writeSerial(F("Ram: "));
  writeSerialLine(freeRam());
}

void displaySplashScreen(){
  //writeSerialLine(F("Showing Splash Screen..."));
  //CUR_TAB_LEVEL++;
  
  //TFT.fillScreen(ILI9341_BLACK);
  
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(4);
  TFT.println(F("Walking Stick\nPrompter\n"));
  
  TFT.setTextSize(3);
  TFT.print(F("V"));
  
  TFT.setTextColor(ILI9341_GREEN);
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
  
  
  //CUR_TAB_LEVEL--;
  //writeSerialLine(DONE_STR);
}

void displayErrMessage(const __FlashStringHelper * message){
  writeSerialLine(message);
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_RED);
  TFT.setTextSize(3);
  TFT.println(message);
  
  while(1);
}


//TODO:: add thing to write to tft notifying of sd activity
//TODO:: add thing to clear sd activity notifier

#endif
