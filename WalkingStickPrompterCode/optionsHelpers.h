#ifndef OPTIONS_HELPERS_H
#define OPTIONS_HELPERS_H

#include "sdHelpers.h"
#include <LinkedList.h>

void selectNewTextSizeOption(){
  const int minVal = 1;
  const int maxVal = 5;
  int curButtonPress = -1;
  
  const int original = OPTIONS.readingFontSize;
  do{
    TFT.fillScreen(ILI9341_BLACK);
    TFT.setCursor(0, 0);
    TFT.setTextSize(MENU_FONT_SIZE);
    TFT.println(F("Select a reading size:"));
    printSepToTFT(MENU_FONT_SIZE);
    
    TFT.println(OPTIONS.readingFontSize);
    TFT.println();
    
    TFT.println(F("Example:"));
    TFT.println();
    TFT.setTextSize(OPTIONS.readingFontSize);
    TFT.println(F("Example"));
    TFT.setTextSize(MENU_FONT_SIZE);
    TFT.println();
    
    TFT.print(F("Columns: "));
    TFT.print(getNumCols(OPTIONS.readingFontSize));
    
    
    curButtonPress = waitForButtonPress();
    
    if(curButtonPress == UP_BUTTON){
      OPTIONS.readingFontSize++;
    }
    if(curButtonPress == DOWN_BUTTON){
      OPTIONS.readingFontSize--;
    }
    
    if(OPTIONS.readingFontSize > maxVal){
      OPTIONS.readingFontSize = maxVal;
    }
    if(OPTIONS.readingFontSize < minVal){
      OPTIONS.readingFontSize = minVal;
    }
    
  }while(curButtonPress != BACK_BUTTON && curButtonPress != YES_BUTTON);
  
  if(curButtonPress == BACK_BUTTON){
    OPTIONS.readingFontSize = original;
  }
}
void selectNewTextColorOption(){

}


void doOptions(){
  LinkedList<MenuEntry*> entries = LinkedList<MenuEntry*>();
  const int textSizeOptionId = 0;
  const int textColorOptionId = 1;
  
  entries.add(new MenuEntry(textSizeOptionId, F("Reading Text Size")));
  entries.add(new MenuEntry(textColorOptionId, F("Reading Text Color")));
  
  int curSelectedId = -1;
  do{
    MenuEntry* selected = selectEntry(F("Select an Option:"), &entries);
    
    if(selected == NULL){
      curSelectedId = -1;
      continue;
    } else {
      curSelectedId = selected->getId();
    }
    
    switch(curSelectedId){
      case textSizeOptionId:
        selectNewTextSizeOption();
        break;
      case textColorOptionId:
        selectNewTextColorOption();
        break;
    }
    
    writeOptions();
    readOptions();
  } while(curSelectedId > -1);
  
  
  while(entries.size() > 0){
    MenuEntry* cur = entries.shift();
    delete cur;
  }
}



#endif
