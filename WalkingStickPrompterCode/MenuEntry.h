#ifndef MENU_ENTRY_H
#define MENU_ENTRY_H

#include <Array.h>
#include "globals.h"

//typedef Array<MenuEntry*, 10> MenuEntries;

class MenuEntry {
private:
    int id;
    const __FlashStringHelper * labelPointer;
    const String labelStr;
    bool flash = false;// flag to determine if pointer is flash or String
    bool clearDataOnDestruct = true;

public:
    /**
     *  don't use, for handling arrays of MenuEntries
     */
    //MenuEntry();
    
    MenuEntry(int idIn, const String labelIn);
    
    MenuEntry(int idIn, const __FlashStringHelper * labelIn);
    
    int getId();
    
    bool isFlash();
    
    const String getLabelStr();
    
    const __FlashStringHelper* getLabelFlash();
        
    ~MenuEntry();
};

#endif
