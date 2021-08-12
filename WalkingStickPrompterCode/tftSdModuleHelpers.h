#ifndef TFT_SD_MODULE_HELPERS_H
#define TFT_SD_MODULE_HELPERS_H

#include "Arduino.h"
#include "globals.h"


void setupUseTFT(){
  digitalWrite(SD_CS, HIGH);
  digitalWrite(TFT_CS, LOW);
}

void setupUseSD(){
  digitalWrite(TFT_CS, HIGH);
  digitalWrite(SD_CS, LOW);
}



#endif
