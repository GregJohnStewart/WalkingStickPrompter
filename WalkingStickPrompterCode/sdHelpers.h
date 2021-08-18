#ifndef SD_HELPERS_H
#define SD_HELPERS_H

#include "globals.h"
#include "tftSdModuleHelpers.h"
#include "SD.h"


const int getNumFilesInDir(char* dirLoc){
  writeSerial(F("Getting number of files in "));
  writeSerialLine(dirLoc);
  CUR_TAB_LEVEL++;
  
  File dir = SD.open(dirLoc);
  int i = 0;
  File curEntry;
    do {
      curEntry = dir.openNextFile();
      if(!curEntry){
        break;
      }
      if(curEntry.name()[0] == "."){
        continue;
      }
      if (curEntry.isDirectory()) {
        continue;
      }
      writeSerialLine(curEntry.name());
      i++;
    }while(true);
  dir.close();
  
  CUR_TAB_LEVEL--;
  writeSerial(F("Done ("));
  writeSerial(i);
  writeSerialLine(F(")"));
  return i;
}

const char* selectFile(){
  writeSerialLine(F("Selecting file..."));
  CUR_TAB_LEVEL++;
  //inline SdVolume volume;
  
  //TODO:: get file list into MenuEntries, ignore '.*' files
  
  //TODO:: pass to MenuEntries Selector to get entry
  //TODO:: return file
  
  const char* dir = (const char PROGMEM *)F("/");
  const int numFiles = getNumFilesInDir(dir);
  MenuEntry* entries = new MenuEntry[numFiles];
  writeSerialLine(F("created arr of entries"));
  File root = SD.open(dir);
  writeSerialLine(F("Opened root"));
  
  writeSerialLine(F("Getting File List"));
  CUR_TAB_LEVEL++;
  {
    int i = 0;
    File curEntry;
    do {
      curEntry = root.openNextFile();
      if(!curEntry){
        break;
      }
      if(curEntry.name()[0] == "."){
        continue;
      }
      if (curEntry.isDirectory()) {
        continue;
      }
      writeSerial(i);
      writeSerial(F(" "));
      writeSerial(curEntry.name());
      entries[i] = MenuEntry(i, curEntry.name());
      i++;
    }while(true);
  }
  root.close();
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  
  MenuEntry selected = selectEntry(F("Select a file:"), entries, numFiles);
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  return selected.getLabelCopy();
}


void setupSD(){
  writeSerialLine(F("Setting up SD..."));
  CUR_TAB_LEVEL++;
  
  Sd2Card SD_CARD;
  SdVolume SD_VOLUME;
  
  if (!SD_CARD.init(SPI_HALF_SPEED, SD_CS)) {    
    displayErrMessage(F("SD Card inserted?"), false);
    alertStatus(SD_ERR_IND, true);
  }
  
  if (!SD_VOLUME.init(SD_CARD)) {    
    displayErrMessage(F("SD Card FAT?"), false);
    alertStatus(SD_ERR_IND, true);
  }
  
  if (!SD.begin(SD_CS)) {
    displayErrMessage(F("SD CARD ERR"), false);
    alertStatus(SD_ERR_IND, true);
  }
  
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Setting up SD."));
}

#endif
