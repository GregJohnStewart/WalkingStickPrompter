#ifndef SD_HELPERS_H
#define SD_HELPERS_H

#include "globals.h"
#include "tftSdModuleHelpers.h"


String selectFile(){
  //inline SdVolume volume;
  SdFile root;
  
  //TODO:: get file list into MenuEntries, ignore '.*' files
  
  //TODO:: pass to MenuEntries Selector to get entry
  //TODO:: return file
  MenuEntry entries[0];
  
  MenuEntry* selected = selectEntry(F("Select a file:"), entries);
}







void setupSD(){
  writeSerialLine(F("Setting up SD..."));
  CUR_TAB_LEVEL++;
  
  if (!SD_CARD.init(SPI_HALF_SPEED, SD_CS)) {    
    displayErrMessage(F("SD Card inserted?"), false);
    alertStatus(SD_ERR_IND, true);
  }
  
  if (!SD_VOLUME.init(SD_CARD)) {    
    displayErrMessage(F("SD Card FAT?"), false);
    alertStatus(SD_ERR_IND, true);
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Setting up SD."));
}

#endif
