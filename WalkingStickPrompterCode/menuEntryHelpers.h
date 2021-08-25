#ifndef MENU_ENTRY_HELPERS_H
#define MENU_ENTRY_HELPERS_H

#include "screenSizeHelpers.h"
#include <LinkedList.h>

void printSepToTFT(int fontSize){
  int numCols = getNumCols(fontSize);
  for(int i = 0; i < numCols; i++){
    TFT.print(F("-"));
  }
}


void drawMenu(const __FlashStringHelper * title, LinkedList<MenuEntry*>* entries, int numEntries, int selected){
  writeSerialLine(F("Drawing Menu..."));
  CUR_TAB_LEVEL++;

  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(MENU_FONT_SIZE);
  TFT.println(title);
  printSepToTFT(MENU_FONT_SIZE);
  
  for(int i = 0; i < numEntries; i++){
    if(i == selected){
      TFT.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    }
  
//    writeSerial(entries[i].getId());
//    writeSerial(F(" "));
//    writeSerialLine(entries[i].getLabel());
    MenuEntry* curEntry = entries->get(i);
    
    
    if(curEntry->isFlash()){
      TFT.println(curEntry->getLabelFlash());
    } else {
      TFT.println(curEntry->getLabelStr());
    }
    
    if(i == selected){
      TFT.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Drawing Menu."));
}

MenuEntry* selectEntry(const __FlashStringHelper * title, LinkedList<MenuEntry*>* entries){
  writeSerialLine(F("Selecting entry..."));
  CUR_TAB_LEVEL++;
  outFreeRam();
  
  int curSelection = 0;
  int buttonPressed = -1;
  int numEntries = entries->size();
  
  do{
    drawMenu(title, entries, numEntries, curSelection);
  
    buttonPressed = waitForButtonPress();
    
    switch(buttonPressed){
      case UP_BUTTON:
        curSelection --;
        break;
      case DOWN_BUTTON:
        curSelection ++;
        break;
    }
    if(curSelection < 0){
      curSelection = numEntries - 1;
    }
    if(curSelection >= numEntries){
      curSelection = 0;
    }
  }while(buttonPressed != SELECT_BUTTON && buttonPressed != BACK_BUTTON);
  
  //TODO:: handle back button 
  
  CUR_TAB_LEVEL--;
  writeSerial(F("DONE Selecting entry ("));
  writeSerial(curSelection);
  writeSerialLine(F(")"));
  
  
  
  return entries->get(curSelection);
}

#endif
