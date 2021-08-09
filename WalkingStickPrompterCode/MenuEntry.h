#ifndef MENU_ENTRY_H
#define MENU_ENTRY_H

#include <Array.h>
#include "globals.h"

//typedef Array<MenuEntry*, 10> MenuEntries;

class MenuEntry {
private:
    int id;
    String label;
    MenuEntry* parent;
    Array<MenuEntry, MAX_NUM_MENU_ENTRIES>* subEntries;

public:
    /**
     *  For basic menu entries
     */
    MenuEntry(int idIn, String &labelIn);
    /**
     *  For basic menu entries
     */
    MenuEntry(String &labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn);
    
    int getId();
    
    String getLabel();
    
    MenuEntry* getParent();
    
    bool hasParent();
    
    Array<MenuEntry, MAX_NUM_MENU_ENTRIES>* getSubEntries();
    
    bool hasSubEntries();
    
};

#endif
