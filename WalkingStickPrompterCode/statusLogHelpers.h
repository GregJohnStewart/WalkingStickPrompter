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

void alertStatus(int ind){
  turnStatusLightOff();
  for(int i = 0; i < ind; i++){
    turnStatusLightOn();
    delay(ALERT_STATUS_BLINK_ON_DUR);
    turnStatusLightOff();
    delay(ALERT_STATUS_BLINK_OFF_DUR);
  }
}


String getTabs(int numTabs){
  String tabs = "";

  for(int i = 0; i < numTabs; i++){
    tabs += "\t";
  }
  return tabs;
}

void writeSerial(bool newline, String line){
  if(!SERIAL_LOGS_ENABLED){
    return;
  }
  String tabs = getTabs(CUR_TAB_LEVEL);
  
  if(newline){
    Serial.println(tabs + line);
  } else {
    Serial.print(tabs + line);
  }
}

void writeSerial(String line){
  writeSerial(false, line);
}

void writeSerialLine(String line){
  writeSerial(true, line);
}


void displaySplashScreen(){
  writeSerialLine(F("Displaying Splash Screen..."));
  CUR_TAB_LEVEL++;
  
  
  
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(3.5);
  TFT.println(F("Walking Stick Prompter"));
  
  TFT.setTextSize(3);
  TFT.print(F("Version: "));
  
  TFT.setTextColor(ILI9341_YELLOW);
  TFT.println(VERSION);
  
  TFT.setTextColor(ILI9341_WHITE);
  
  
  for(int i = 1; i <= 5; i++){
    TFT.setTextSize(i);
    TFT.println(i);
  }
  
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Displaying Splash Screen."));
}


//TODO:: add thing to write to tft notifying of sd activity
//TODO:: add thing to clear sd activity notifier

#endif
