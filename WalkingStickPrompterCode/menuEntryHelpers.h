#ifndef MENU_ENTRY_HELPERS_H
#define MENU_ENTRY_HELPERS_H

#include "screenSizeHelpers.h"

String getSep(int fontSize){
  String output = "";
  
  for(int i = 0; i < getNumCols(fontSize); i++){
    output += F("-");
  }
  return output;
}


void drawMenu(String title, MenuEntry entries[], int selected){
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.setTextColor(ILI9341_WHITE);
  TFT.setTextSize(MENU_FONT_SIZE);
  TFT.println(title);
  TFT.println(getSep(MENU_FONT_SIZE));
  
  
}





MenuEntry* selectEntry(String title, MenuEntry entries[]){
  
  int curSelection = 0;
  
  drawMenu(title, entries, curSelection);
  
  waitForButtonPress();
}

#endif
