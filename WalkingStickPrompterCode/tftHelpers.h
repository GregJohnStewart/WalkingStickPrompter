#ifndef TFT_HELPERS_H
#define TFT_HELPERS_H

#include "globals.h"

void setupTft(){
  //writeSerialLine(F("Setting up TFT Display..."));
  //CUR_TAB_LEVEL++;
  TFT.begin();
  TFT.setRotation(3);
  //{
    //uint8_t x = TFT.readcommand8(ILI9341_RDMODE);
    //writeSerialLine("Display Power Mode: 0x" + String(x, HEX));
    //x = TFT.readcommand8(ILI9341_RDMADCTL);
    //writeSerialLine("MADCTL Mode: 0x" + String(x, HEX));
    //x = TFT.readcommand8(ILI9341_RDPIXFMT);
    //writeSerialLine("Pixel Format: 0x" + String(x, HEX));
    //x = TFT.readcommand8(ILI9341_RDIMGFMT);
    //writeSerialLine("Image Format: 0x" + String(x, HEX));
    //x = TFT.readcommand8(ILI9341_RDSELFDIAG);
    //writeSerialLine("Self Diagnostic: 0x" + String(x, HEX));
    //writeSerialLine("Height: " + String(TFT.height()));
    //writeSerialLine("Width: " + String(TFT.width()));
  //}
  TFT.fillScreen(ILI9341_BLACK);
  //CUR_TAB_LEVEL--;
  //writeSerialLine(DONE_STR);
}


#endif
