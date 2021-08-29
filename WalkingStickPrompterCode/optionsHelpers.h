#ifndef OPTIONS_HELPERS_H
#define OPTIONS_HELPERS_H

#include "sdHelpers.h"
#include <LinkedList.h>
#include "Adafruit_ILI9341.h"

void selectNewTextSizeOption(){
  const int minVal = 1;
  const int maxVal = 5;
  int curButtonPress = -1;
  
  const int original = OPTIONS.readingFontSize;
  do{
    TFT.fillScreen(ILI9341_BLACK);
    TFT.setCursor(0, 0);
    TFT.setTextSize(MENU_FONT_SIZE);
    TFT.println(F("Reading Text Size:"));
    printSepToTFT(MENU_FONT_SIZE);
    
    TFT.println(OPTIONS.readingFontSize);
    TFT.println();
    
    TFT.println(F("Example:"));
    TFT.println();
    TFT.setTextSize(OPTIONS.readingFontSize);
    TFT.println(F("Text"));
    TFT.setTextSize(MENU_FONT_SIZE);
    TFT.println();
    
    TFT.print(F("Cols: "));
    TFT.println(getNumCols(OPTIONS.readingFontSize));
    TFT.print(F("Rows: "));
    TFT.println(getNumRows(OPTIONS.readingFontSize));
    
    
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
  LinkedList<MenuEntry*> entries = LinkedList<MenuEntry*>();
  
  entries.add(new MenuEntry(ILI9341_WHITE, F("White")));
  entries.add(new MenuEntry(ILI9341_RED, F("Red")));
  entries.add(new MenuEntry(ILI9341_DARKGREY, F("Grey")));
  entries.add(new MenuEntry(ILI9341_GREENYELLOW, F("Lime")));
  
  MenuEntry* selected = selectEntry(F("Colors:"), &entries);
  
  if(selected != NULL){
    OPTIONS.readingFontColor = selected->getId();
  }
  
  while(entries.size() > 0){
    MenuEntry* cur = entries.shift();
    delete cur;
  }
}
void selectNewBacklightOption(){
  const byte minVal = 15;
  const byte maxVal = 255;
  const byte incNum = (maxVal - minVal) / 4;
  
  int curButtonPress = -1;
  
  const byte original = OPTIONS.backlightLevel;
  do{
    analogWrite(TFT_BACKLIGHT, OPTIONS.backlightLevel);
    TFT.fillScreen(ILI9341_BLACK);
    TFT.setCursor(0, 0);
    TFT.setTextSize(MENU_FONT_SIZE);
    TFT.println(F("Backlight\n"));
    TFT.print(F("Value: "));
    TFT.println(OPTIONS.backlightLevel);
    TFT.println();
    TFT.setTextColor(OPTIONS.readingFontColor);
    TFT.setTextSize(OPTIONS.readingFontSize);
    TFT.println(F("Example Txt\n"));
    TFT.setTextColor(ILI9341_WHITE);
    
    
    
    
    curButtonPress = waitForButtonPress();
    
    if(curButtonPress == UP_BUTTON){
      if(OPTIONS.backlightLevel != maxVal){
        OPTIONS.backlightLevel += incNum;
      }
    }
    if(curButtonPress == DOWN_BUTTON){
      if(OPTIONS.backlightLevel != minVal){
        OPTIONS.backlightLevel -= incNum;
      }
    }
  }while(curButtonPress != BACK_BUTTON && curButtonPress != YES_BUTTON);
  
  if(curButtonPress == BACK_BUTTON){
    OPTIONS.backlightLevel = original;
  }
}


void doOptions(){
  LinkedList<MenuEntry*> entries = LinkedList<MenuEntry*>();
  const int textSizeOptionId = 0;
  const int textColorOptionId = 1;
  const int backlightOptionId = 2;
  
  entries.add(new MenuEntry(textSizeOptionId, F("Txt Size")));
  entries.add(new MenuEntry(textColorOptionId, F("Txt Color")));
  entries.add(new MenuEntry(backlightOptionId, F("Backlight")));
  
  int curSelectedId = -1;
  do{
    MenuEntry* selected = selectEntry(F("Ops:"), &entries);
    
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
      case backlightOptionId:
        selectNewBacklightOption();
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
