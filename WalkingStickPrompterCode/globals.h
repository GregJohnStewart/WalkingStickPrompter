/**
 * Global variables for WalkingStickPrompter.
 * Author: Greg Stewart
 * 
 * https://github.com/GregJohnStewart/WalkingStickPrompter
 */
#ifndef GLOBALS_H
#define GLOBALS_H

#include "Arduino.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SD.h>
#include "Options.h"

/*
 * Basics
 */
//version
inline const char VERSION[6] = "0.0.1";
inline int CUR_TAB_LEVEL = 0;

/**
 * Serial Logging
 */
inline bool SERIAL_LOGS_ENABLED = true;
inline const int SERIAL_LOG_BAUD = 9600;

/*
 * Status
 */
// status led pin
inline const int STATUS_LED = LED_BUILTIN;
inline const unsigned int ALERT_STATUS_BLINK_ON_DUR = 500;
inline const unsigned int ALERT_STATUS_BLINK_OFF_DUR = 500;
//indicators
inline const unsigned int TFT_ERR_IND = 2;
inline const unsigned int SD_ERR_IND = 3;

/*
 * Button
 */
// up button
inline const unsigned int UP_BUTTON = 4;
inline const unsigned int DOWN_BUTTON = 3;
inline const unsigned int LEFT_BUTTON = 2;
inline const unsigned int RIGHT_BUTTON = 10;

inline const unsigned int BUTT_ARR[] = {UP_BUTTON, DOWN_BUTTON, LEFT_BUTTON, RIGHT_BUTTON};

inline const unsigned int YES_BUTTON = RIGHT_BUTTON;
inline const unsigned int NO_BUTTON = LEFT_BUTTON;
inline const unsigned int CANCEL_BUTTON = LEFT_BUTTON;
inline const unsigned int SELECT_BUTTON = RIGHT_BUTTON;
inline const unsigned int BACK_BUTTON = LEFT_BUTTON;

/*
 * Menu Entries
 */
inline const unsigned int MAX_NUM_MENU_ENTRIES = 10;

/*
 * TFT/SD Pins
 */
inline const unsigned int TFT_CS = 6;
inline const unsigned int TFT_DC = 9;
inline const unsigned int TFT_RST = -1;
 
 
/*
 * TFT Objects
 */
inline Adafruit_ILI9341 TFT = Adafruit_ILI9341(TFT_CS, TFT_DC);

/*
 * Globals for TFT
 */
//big array indexed by the text size to use
inline int BASE_FONT_HEIGHT = 8;//pixels
inline int BASE_FONT_WIDTH = 6;//pixels
inline int MENU_FONT_SIZE = 2;

/*
 * SD Objects
 */



/*
 * Globals for SD
 */
inline const int SD_CS = 5;

/*
 * Options
 */
inline Options OPTIONS = Options();
inline char OPTIONS_FILE[9] = "/ops.dat";


#endif
