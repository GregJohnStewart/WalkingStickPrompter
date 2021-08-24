#ifndef SD_HELPERS_H
#define SD_HELPERS_H

#include "globals.h"
#include "tftSdModuleHelpers.h"
#include "SD.h"
#include <LinkedList.h>


const char validFile(File* file){
  if(!*file){
    return -1;
  }
  if(file->name()[0] == "."){
    return 0;
  }
  if(file->isDirectory()) {
    return 0;
  }
  //TODO:: only allow .txt

  
  return 1;
}

const int getNumFilesInDir(const char* dirLoc){
  writeSerial(F("Getting number of files in "));
  writeSerialLine(dirLoc);
  CUR_TAB_LEVEL++;
  
  File dir = SD.open(dirLoc);
  int i = 0;
  File curEntry;
    do {
      curEntry = dir.openNextFile();
      const char testResult = validFile(&curEntry);
      if(testResult == -1){
        curEntry.close();
        break;
      }
      if(!testResult){
        curEntry.close();
        continue;
      }
      writeSerial(false, true, F("\""));
      writeSerial(false, false, curEntry.name());
      writeSerial(true, false, F("\""));
      i++;
      curEntry.close();
    }while(true);
  dir.close();
  
  CUR_TAB_LEVEL--;
  writeSerial(false, true, F("Done ("));
  writeSerial(i);
  writeSerial(true, false, F(")"));
  return i;
}

const String selectFile(){
  writeSerialLine(F("Selecting file..."));
  CUR_TAB_LEVEL++;
  //inline SdVolume volume;
  
  //TODO:: get file list into MenuEntries, ignore '.*' files
  
  //TODO:: pass to MenuEntries Selector to get entry
  //TODO:: return file
  
  const char* dir = "/";
  const int numFiles = getNumFilesInDir(dir);
  LinkedList<MenuEntry*> entries = LinkedList<MenuEntry*>();
  
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
      const char testResult = validFile(&curEntry);
      if(testResult == -1){
        curEntry.close();
        break;
      }
      if(!testResult){
        curEntry.close();
        continue;
      }
      
      const char* curEntryName = curEntry.name();
      writeSerial(false, true, F("\""));
      writeSerial(false, false, curEntryName);
      writeSerial(false, false, F("\" - "));
      String labelStrIn = String(curEntryName);
      MenuEntry* curMenuEntry = new MenuEntry(i, labelStrIn);
      entries.add(curMenuEntry);
      writeSerial(i);
      writeSerial(false, false, F(" "));
      
      String labelStr = entries.get(i)->getLabelStr();
      writeSerial(false, false, F("\""));
      writeSerial(false, false, labelStr.c_str());
      writeSerial(true, false, F("\""));
      i++;
      curEntry.close();
    }while(true);
  }
  root.close();
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  
  MenuEntry* selected = selectEntry(F("Select a file:"), &entries);
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  
  return selected->getLabelStr();
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
