/**
 * Main code for the WalkingStick Prompter.
 * Author: Greg Stewart
 * 
 * https://github.com/GregJohnStewart/WalkingStickPrompter
 */
 #include "globals.h"
 #include "statusLogHelpers.h"
 #include "buttonHelpers.h"

void setup() {
  // Setup, turn on status light during setup
  pinMode(LED_BUILTIN, OUTPUT);
  turnStatusLightOn();

  setupButtons();


  //setup TFT display, display something simple
  

  //setup SD card info

  //display basic infos
  
  // done with setup
  turnStatusLightOff();
}

/**
 * Logic goes as follows:
 * 
 *  1. quick check for TFT/SD operability.
 *    - if either not, blink status led accordingly, wait 2.5 seconds, and go around
 *  2. Display all files
 *  3. wait for input
 *    - up/down, scroll file selection
 *    - yes button, show file
 *      - scroll enable through file
 *      - no button, done, back around
 *    - no button, show options
 *      - scroll through options, set as needed
 *      - no button, done, back around
 *  4. Done
 */
void loop() {
  waitForButtonPress();
  waitForButtonPress(-1);
}
