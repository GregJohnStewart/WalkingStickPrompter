#ifndef SD_HELPERS_H
#define SD_HELPERS_H

#include "globals.h"
#include "tftSdModuleHelpers.h"


void setupSD(){
  writeSerialLine(F("Setting up SD..."));
  CUR_TAB_LEVEL++;
  
  setupUseSD();
  
  if (!card.init(SPI_HALF_SPEED, CHIP_SELECT)) {
    writeSerialLine("initialization failed. Things to check:");
    writeSerialLine("* is a card inserted?");
    writeSerialLine("* is your wiring correct?");
    writeSerialLine("* did you change the chipSelect pin to match your shield or module?");
    alertStatus(SD_ERR_IND, true);
  } else {
    Serial.println("Wiring is correct and a card is present.");
  }
  
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Setting up SD."));
}



#endif
