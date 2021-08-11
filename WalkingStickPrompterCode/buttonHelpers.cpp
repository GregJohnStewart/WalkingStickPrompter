
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
  Serial.println("\tButton reading: " + String(reading));

  if(reading != HIGH){
    Serial.println("\tButton was LOW");
    return false;
  }
    Serial.println("\tButton was HIGH");
  unsigned long initialTime = millis();
  do {
    reading = digitalRead(button);
    if(reading == LOW){
      Serial.println("\tBack to LOW");
      return false;
    }
  } while(testTimeout(initialTime, debounceDelay));
  Serial.println("\tStill HIGH");

  return true;
}

/**
 * 
 * @param timeout the length of time to ait for a button press. -1 for indefinately
 * @return the button value, or -1 if timed out
 */
int waitForButtonPress(unsigned long timeout){
  unsigned long startTime = millis();
  
  //writeSerialLine(F("Waiting for button press..."));
  //CUR_TAB_LEVEL++;
  
  do{
    for (int i = 0; i < sizeof BUTT_ARR / sizeof BUTT_ARR[0]; i++) {
      Serial.println("Testing button: " + String(BUTT_ARR[i]));
      if(readButtonState(BUTT_ARR[i])){
      	  //writeSerialLine("Button was pressed: " + BUTT_ARR[i]);
          //CUR_TAB_LEVEL--;
        return BUTT_ARR[i];
      }
    }
  }while(timeout == -1 || testTimeout(startTime, timeout));
  
  //writeSerialLine(F("Timed out."));
  //CUR_TAB_LEVEL--;
  
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
