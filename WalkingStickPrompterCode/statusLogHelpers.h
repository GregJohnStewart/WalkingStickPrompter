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

void writeSerialLine(int numTabs, char line[]){
  if(!SERIAL_LOGS_ENABLED){
    return;
  }
  
  String tabs = "";

  for(int i = 0; i < numTabs; i++){
    tabs += "\t";
  }
  
  Serial.println(tabs + line);
}

void writeSerialLine(char line[]){
  writeSerialLine(0, line);
}

//TODO:: add thing to write to tft notifying of sd activity
//TODO:: add thing to clear sd activity notifier

#endif
