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
inline const char VERSION[] = "0.0.1";

/**
 * Serial Logging
 */
inline const bool SERIAL_LOGS_ENABLED = true;
inline const int SERIAL_LOG_BAUD = 9600;

/*
 * Status
 */
// status led pin
inline const int STATUS_LED = LED_BUILTIN;
inline const unsigned int ALERT_STATUS_BLINK_ON_DUR = 100;
inline const unsigned int ALERT_STATUS_BLINK_OFF_DUR = 250;
//indicators
inline const unsigned int TFT_ERR_IND = 2;
inline const unsigned int SD_ERR_IND = 3;

/*
 * Button
 */
// up button
inline const unsigned int UP_BUTTON = 4;
// down button
inline const unsigned int DOWN_BUTTON = 3;
// left button
inline const unsigned int LEFT_BUTTON = 2;
// right button
inline const unsigned int RIGHT_BUTTON = 10;

inline const unsigned int BUTT_ARR[] = {UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON};

// yes button
inline const unsigned int YES_BUTTON = RIGHT_BUTTON;
// no button
inline const unsigned int NO_BUTTON = LEFT_BUTTON;
// cancel button
inline const unsigned int CANCEL_BUTTON = LEFT_BUTTON;

/*
 * Menu Entries
 */
inline const unsigned int MAX_NUM_MENU_ENTRIES = 10;

/*
 * TFT/SD Pins
 */


#endif
