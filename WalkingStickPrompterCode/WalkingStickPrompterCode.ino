/**
   Main code for the WalkingStick Prompter.
   Author: Greg Stewart

   https://github.com/GregJohnStewart/WalkingStickPrompter
*/
#include "globals.h"
#include "statusLogHelpers.h"
#include "buttonHelpers.h"
#include "MenuEntry.h"
#include "tftHelpers.h"
#include "screenSizeHelpers.h"

int temp = 1;

void setup() {
  // Setup, turn on status light during setup
  pinMode(STATUS_LED, OUTPUT);
  turnStatusLightOn();

  Serial.begin(SERIAL_LOG_BAUD);
  writeSerialLine(F("\n\n\nBegin Setup..."));
  CUR_TAB_LEVEL++;
  
  Serial.println("High: " + String(HIGH));
  Serial.println("Low: " + String(LOW));

  setupButtons();

  writeSerialLine(F("Done Setting up Buttons."));
  writeSerialLine("Status LED pin: " + String(STATUS_LED));
  


  //setup TFT display, display something simple
  setupTft();


  //setup SD card info
  writeSerialLine(F("Done Setting up SD."));

  //display basic infos
  displaySplashScreen();

  // done with setup
  turnStatusLightOff();

  writeSerialLine(F("Setup Complete."));
  delay(5000);
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
  /*
    for(double i = 1; i < 10; i += 0.1){
    TFT.setTextSize(i);
    TFT.println(i);
    delay(250);
    }
  */
  
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
  
  /* */
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setCursor(0, 0);
  TFT.print("Waiting for button press...");
  
  temp = waitForButtonPress();
  
  TFT.setCursor(0, 0);
  TFT.fillScreen(ILI9341_BLACK);
  TFT.print(String(temp) + " Was Pressed!");
  /* */

  delay(2000);
}
