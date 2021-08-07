/**
 * Global variables for WalkingStickPrompter.
 * Author: Greg Stewart
 * 
 * https://github.com/GregJohnStewart/WalkingStickPrompter
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arduino.h"
/*
 * Basics
 */
//version
inline char VERSION[] = "0.0.1";

/*
 * Status
 */
// status led pin
inline int STATUS_LED = LED_BUILTIN;
inline int ALERT_STATUS_BLINK_ON_DUR = 100;
inline int ALERT_STATUS_BLINK_OFF_DUR = 250;
//indicators
inline int TFT_ERR_IND = 2;
inline int SD_ERR_IND = 3;

/*
 * Button pins
 */
// up button
inline int UP_BUTTON = 4;
// down button
inline int DOWN_BUTTON = 3;
// left button
inline int LEFT_BUTTON = 2;
// right button
inline int RIGHT_BUTTON = 10;

// yes button
inline int YES_BUTTON = 10;
// no button
inline int NO_BUTTON = 2;
// cancel button
inline int CANCEL_BUTTON = 2;

/*
 * TFT/SD Pins
 */


#endif
