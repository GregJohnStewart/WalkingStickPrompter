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

void setup() {
  // Setup, turn on status light during setup
  pinMode(STATUS_LED, OUTPUT);
  turnStatusLightOn();

  Serial.begin(SERIAL_LOG_BAUD);
  writeSerialLine(F("\n\n\nBegin Setup..."));
  CUR_TAB_LEVEL++;

  setupButtons();

  writeSerialLine(F("Done Setting up Buttons."));


  //setup TFT display, display something simple
  setupTft();


  //setup SD card info
  writeSerialLine(F("Done Setting up SD."));

  //display basic infos
  displaySplashScreen();

  // done with setup
  turnStatusLightOff();

  writeSerialLine(F("Setup Complete."));
  TFT.fillScreen(ILI9341_BLACK);
  TFT.setTextColor(ILI9341_WHITE, ILI9341_BLACK);
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
  

  String text = " . . Text scrolling on Adafruit TFT shield . ."; // sample text

  const int width = 18; // width of the marquee display (in characters)

  // Loop once through the string

  for (int offset = 0; offset < text.length(); offset++){

    // Construct the string to display for this iteration
    String t = "";
    for (int i = 0; i < width; i++) {
      t += text.charAt((offset + i) % text.length());
    }

    // Print the string for this iteration

    TFT.setCursor(0, TFT.height() / 2 - 10); // display will be halfway down screen

    TFT.print(t);

    // Short delay so the text doesn't move too fast

    delay(200);

  }


}
