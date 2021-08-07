#include "Arduino.h"
#include "globals.h"

// the debounce time; increase if the output flickers
unsigned long debounceDelay = 50;

bool testTimeout(unsigned long start, unsigned long cur, unsigned long timeout){
  return cur - start <= timeout;
}
bool testTimeout(unsigned long start, unsigned long timeout){
  return testTimeout(start, millis(), timeout);
}

bool readButtonState(int button){
  int reading = digitalRead(button);
  // read the state of the switch into a local variable:

  if(reading == LOW){
    return false;
  }
  unsigned long initialTime = millis();
  do {
    reading = digitalRead(button);
    if(reading == LOW){
      return false;
    }
  } while(testTimeout(initialTime, debounceDelay));

  return true;
}

/**
 * 
 * @param timeout the length of time to ait for a button press. -1 for indefinately
 * @return the button value, or -1 if timed out
 */
int waitForButtonPress(unsigned long timeout){
  unsigned long startTime = millis();

  do{
    for (int i = 0; i < sizeof BUTT_ARR / sizeof BUTT_ARR[0]; i++) {
      if(readButtonState(BUTT_ARR[i])){
        return BUTT_ARR[i];
      }
    }
  }while(timeout == -1 || testTimeout(startTime, timeout));
  
  return -1;
}

int waitForButtonPress(){
  return waitForButtonPress(-1);
}

void setupButtons(){
  pinMode(UP_BUTTON, INPUT);
  pinMode(DOWN_BUTTON, INPUT);
  pinMode(LEFT_BUTTON, INPUT);
  pinMode(RIGHT_BUTTON, INPUT);
}
