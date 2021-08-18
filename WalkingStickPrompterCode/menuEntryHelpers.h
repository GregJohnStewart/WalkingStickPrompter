#ifndef MENU_ENTRY_HELPERS_H
#define MENU_ENTRY_HELPERS_H

#include "screenSizeHelpers.h"

char* getSep(int fontSize){
  int numCols = getNumCols(fontSize);
  char* output = new char[numCols + 1];
  
  for(int i = 0; i < numCols; i++){
    output[i] = F("-");
  }
  return output;
}


void drawMenu(char* title, MenuEntry entries[], int numEntries, int selected){
  writeSerialLine(F("Drawing Menu..."));
  CUR_TAB_LEVEL++;

  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(MENU_FONT_SIZE);
  TFT.println(title);
  TFT.println(getSep(MENU_FONT_SIZE));
  
  for(int i = 0; i < numEntries; i++){
    if(i == selected){
      TFT.setTextColor(ILI9341_BLACK, ILI9341_WHITE);
    }
  
    writeSerial(entries[i].getId());
    writeSerial(" ");
    writeSerialLine(entries[i].getLabel());
    
    
    TFT.println(entries[i].getLabel());
    
    if(i == selected){
      TFT.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
    }
  }
  
  CUR_TAB_LEVEL--;
  writeSerialLine(F("Done Drawing Menu."));
}

MenuEntry selectEntry(char* title, MenuEntry entries[], int numEntries){
  writeSerialLine(F("Selecting entry..."));
  CUR_TAB_LEVEL++;
  
  int curSelection = 0;
  int buttonPressed = -1;
  
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
  
  return entries[curSelection];
}

MenuEntry selectEntry(const __FlashStringHelper * title, MenuEntry entries[], int numEntries){
    return selectEntry((const char PROGMEM *)title, entries, numEntries);
}

#endif
