#ifndef OPTIONS_H
#define OPTIONS_H

#include "Adafruit_ILI9341.h"

class Options {
private:
  //unsigned int readingFontSize = 1;
  //unsigned int readingFontColor = ILI9341_WHITE;

public:
  unsigned int readingFontSize = 2;
  unsigned int readingFontColor = ILI9341_WHITE;
  byte backlightLevel = 255;
};

#endif
