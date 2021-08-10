#ifndef SCREEN_SIZE_HELPERS_H
#define SCREEN_SIZE_HELPERS_H

#include "globals.h"

int getNumRows(int fontSize){
  return TFT.width() / (BASE_FONT_WIDTH * fontSize);
}

int getNumCols(int fontSize){
  return TFT.height() / (BASE_FONT_HEIGHT * fontSize);
}

int getNumChars(int fontSize){
  return getNumRows(fontSize) * getNumCols(fontSize);
}


#endif
