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

#endif
