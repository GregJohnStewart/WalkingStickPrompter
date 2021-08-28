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
  //only allow .txt
  int len = strlen(file->name());
  //writeSerialLine(&(file->name()[len]) - 3);
  if(strcmp("TXT", &(file->name()[len]) - 3) != 0){
    return 0;
  }
  
  return 1;
}

const String selectFile(){
  writeSerialLine(F("Selecting file..."));
  CUR_TAB_LEVEL++;
  //inline SdVolume volume;
  
  //TODO:: get file list into MenuEntries, ignore '.*' files
  
  //TODO:: pass to MenuEntries Selector to get entry
  //TODO:: return file
  
  const char* dir = "/";
  //const int numFiles = getNumFilesInDir(dir);
  LinkedList<MenuEntry*> entries = LinkedList<MenuEntry*>();
  
  //writeSerialLine(F("created arr of entries"));
  File root = SD.open(dir);
  //writeSerialLine(F("Opened root"));
  
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
      //writeSerial(false, true, F("\""));
      //writeSerial(false, false, curEntryName);
      //writeSerial(false, false, F("\" - "));
      String labelStrIn = String(curEntryName);
      MenuEntry* curMenuEntry = new MenuEntry(i, labelStrIn);
      entries.add(curMenuEntry);
      //writeSerial(i);
      //writeSerial(false, false, F(" "));
      
      //String labelStr = entries.get(i)->getLabelStr();
      //writeSerial(false, true, F("\""));
      //writeSerial(false, false, labelStr.c_str());
      //writeSerial(true, false, F("\""));
      i++;
      curEntry.close();
    }while(true);
  }
  root.close();
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  
  MenuEntry* selected = selectEntry(F("Select a file:"), &entries);
  
  String output;
  if(selected == NULL){
    output = F("");
  } else {
    output = selected->getLabelStr();
  }
  
  //clean up all menu entries, strings except for chosen string
  while(entries.size() > 0){
    MenuEntry* cur = entries.shift();
    delete cur;
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("DONE."));
  
  if(selected == NULL){
    return output;
  }
  return dir + output;
  
}


void setupSD(){
  writeSerialLine(F("Setting up SD..."));
  CUR_TAB_LEVEL++;
  
  Sd2Card SD_CARD;
  SdVolume SD_VOLUME;
  
  if (!SD_CARD.init(SPI_HALF_SPEED, SD_CS)) {    
    displayErrMessage(F("SD Card in?"), false);
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

void writeOptions(){
  writeSerialLine(F("Writing options to sd..."));
  CUR_TAB_LEVEL++;
  
  File opsFile = SD.open(OPTIONS_FILE, FILE_WRITE | O_TRUNC);
  
  if(!opsFile){
    displayErrMessage(F("Options file\ncould not be\nopened for\nwriting!"), true);
  } else {
    size_t returned = opsFile.write((char*)&OPTIONS, sizeof(OPTIONS));
    opsFile.close();
    
    if(returned == 0 || returned != sizeof(OPTIONS)){
      displayErrMessage(F("Options file\ncould not be\nwritten!"), true);
    }
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done."));
}

void readOptions(){
  writeSerialLine(F("Reading ops from sd..."));
  CUR_TAB_LEVEL++;
  
  File opsFile = SD.open(OPTIONS_FILE, FILE_READ);
  
  if(!opsFile){
    writeSerialLine(F("No ops file."));
    writeOptions();
  } else {
    opsFile.read((char*)&OPTIONS, sizeof(OPTIONS));
    opsFile.close();
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done."));
}

//TODO:: rework to send to TFT from here, read in one line at a time rather than entire screen
void readInContentPage(File file, const unsigned long curFileIndex, char * contentBuffer, const int bufferSize){
  if(!file.seek(curFileIndex)){
    displayErrMessage(F("Error seeking in file."), true);
  }
  
  const int numRead = file.read(contentBuffer, bufferSize);
  
  if(numRead == -1){
    displayErrMessage(F("Error reading\nfile."), true);
  }
  
  contentBuffer[numRead] = '\0';
}

void readFileContent(String location){
  writeSerialLine(F("Reading file content to user."));
  CUR_TAB_LEVEL++;
  
  File file = SD.open(location, FILE_READ);
  if(!file){
    displayErrMessage(F("Unable to open\nfile for reading."), true);
  }
  
  const int numCharsToShow = getNumChars(OPTIONS.readingFontSize);
  const unsigned long fileSize = file.size();
  unsigned long curFileIndex = 0;
  unsigned long indexUpperBound = ((fileSize < numCharsToShow) ? 0 : (fileSize - (numCharsToShow/2)));
  char contentBuffer[numCharsToShow + 1];
  unsigned int buttonPressed = 0;
  
  
  contentBuffer[numCharsToShow] = '\0';//set null terminator, should never be touched when content gets read in
  writeSerial(F("Num chars on screen: "));
  writeSerialLine(numCharsToShow);
  outFreeRam();
  
  TFT.setTextColor(OPTIONS.readingFontColor);
  TFT.setTextSize(OPTIONS.readingFontSize);
  
  do{
    readInContentPage(file, curFileIndex, contentBuffer, numCharsToShow);
    
    TFT.fillScreen(ILI9341_BLACK);
    TFT.setCursor(0, 0);
    TFT.print(contentBuffer);
    
    do{//only allow button press for back, up, and down
      buttonPressed = waitForButtonPress();
    } while(buttonPressed != BACK_BUTTON && buttonPressed != UP_BUTTON && buttonPressed != DOWN_BUTTON);
    
    if(buttonPressed == UP_BUTTON){
      if(curFileIndex <= numCharsToShow){
        curFileIndex = 0;
      } else {
        curFileIndex -= numCharsToShow;
      }
    } else if(buttonPressed == DOWN_BUTTON){
      curFileIndex += numCharsToShow;
      
      if(curFileIndex > indexUpperBound){
        curFileIndex = indexUpperBound;
      }
    }
  } while(buttonPressed != BACK_BUTTON);
  
  file.close();
  
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done."));
}

#endif
