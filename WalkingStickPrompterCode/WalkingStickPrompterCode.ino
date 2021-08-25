/**
   Main code for the WalkingStick Prompter.
   Author: Greg Stewart

   https://github.com/GregJohnStewart/WalkingStickPrompter
*/
#include "globals.h"
#include "statusLogHelpers.h"
#include "buttonHelpers.h"
#include "MenuEntry.h"
#include "menuEntryHelpers.h"
#include "tftHelpers.h"
#include "sdHelpers.h"
#include "tftSdModuleHelpers.h"
#include "screenSizeHelpers.h"

int temp = 1;

void setup() {
  // Setup, turn on status light during setup
  pinMode(STATUS_LED, OUTPUT);
  pinMode(TFT_CS, OUTPUT);
  pinMode(SD_CS, OUTPUT);
  
  turnStatusLightOn();

  Serial.begin(SERIAL_LOG_BAUD);
  if(!Serial){
    SERIAL_LOGS_ENABLED = false;
  }
  
  writeSerialLine(F("\n\n\nBegin Setup..."));
  CUR_TAB_LEVEL++;

  setupButtons();

  writeSerialLine(F("Done Setting up Buttons."));
  
  //setup TFT display, display something simple
  setupTft();


  //setup SD card info
  setupSD();

  //display basic infos
  displaySplashScreen();

  // done with setup
  turnStatusLightOff();
  
  outFreeRam();

  CUR_TAB_LEVEL--;
  writeSerialLine(F("Setup Complete."));
  delay(1000);
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
  TFT.setTextSize(MENU_FONT_SIZE);
}

/**
   Logic goes as follows:

    1. quick check for TFT/SD operability.
      - if either not, blink status led accordingly, wait 2.5 seconds, and go around
    2. Display all files
    3. wait for input
      - up/down, scroll file selection
      - yes button, show file
        - scroll enable through file
        - no button, done, back around
      - no button, show options
        - scroll through options, set as needed
        - no button, done, back around
    4. Done
*/
void loop() {
  writeSerialLine(F("START program cycle"));
  CUR_TAB_LEVEL++;
  outFreeRam();

  const String fileChosen = selectFile();
  outFreeRam();
  
  if(fileChosen.length() > 0){
    writeSerial(F("Chose file: "));
    writeSerialLine(fileChosen.c_str());
    //TODO:: start showing file
  } else {
    //TODO:: open options
  }
  
  outFreeRam();
  CUR_TAB_LEVEL--;
  writeSerialLine(F("END program cycle."));
}


  /* Screen resolutions *
  TFT.fillScreen(ILI9341_BLACK);
  delay(500);
  TFT.setCursor(0, 0);
  TFT.setTextSize(temp);
  
  
  TFT.print(temp);
  for(int i = 2; i < getNumChars(temp); i++){
    TFT.print("_");
  }
  TFT.print("!");
  temp++;
  
  if(temp == 6){
    temp = 1;
  }
  /* */
  
  

  /* Button pressing *
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.print("Waiting for button press...");
  
  temp = waitForButtonPress();
  
  TFT.setCursor(0, 0);
  TFT.fillScreen(ILI9341_BLACK);
  TFT.print(String(temp) + " Was Pressed!");
  delay(2000);
  /* */
