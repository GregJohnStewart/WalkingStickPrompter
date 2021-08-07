#ifndef BUTTON_HELPERS_H
#define BUTTON_HELPERS_H

#include "Arduino.h"
#include "globals.h"

int waitForButtonPress(unsigned long timeout);

int waitForButtonPress();

void setupButtons();

#endif
