#include "MenuEntry.h"

MenuEntry::MenuEntry(){
}

MenuEntry::MenuEntry(int idIn, const String labelIn){
    id = idIn;
    labelStr = labelIn;
    flash = false;
}
 
MenuEntry::MenuEntry(int idIn, const __FlashStringHelper * labelIn){
    id = idIn;
    labelPointer = labelIn;
    flash = true;
}


int MenuEntry::getId(){
    return id;
}

bool MenuEntry::isFlash(){
    return flash;
}

const String MenuEntry::getLabelStr(){
    return labelStr;
}
    
const __FlashStringHelper* MenuEntry::getLabelFlash(){
    return labelPointer;
}

MenuEntry::~MenuEntry(){
    
}
