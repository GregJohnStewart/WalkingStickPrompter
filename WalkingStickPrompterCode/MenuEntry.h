#ifndef MENU_ENTRY_H
#define MENU_ENTRY_H

#include <Array.h>
#include "globals.h"

//typedef Array<MenuEntry*, 10> MenuEntries;

class MenuEntry {
private:
    int id;
    char* label;
    MenuEntry* parent;
    bool clearDataOnDestruct = true;
    Array<MenuEntry, MAX_NUM_MENU_ENTRIES>* subEntries;

public:
    /**
     *  don't use, for handling arrays
     */
    MenuEntry();
    /**
     *  For basic menu entries
     */
    MenuEntry(int idIn, char* labelIn, bool clearDataOnDestructIn);
    
    MenuEntry(int idIn, char* labelIn);
    
    MenuEntry(int idIn, char* labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn, bool clearDataOnDestructIn);
    
    MenuEntry(int idIn, char* labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn);
    
    int getId();
    
    char* getLabel();
    
    char* getLabelCopy();
    
    MenuEntry* getParent();
    
    bool hasParent();
    
    Array<MenuEntry, MAX_NUM_MENU_ENTRIES>* getSubEntries();
    
    bool hasSubEntries();
    
    ~MenuEntry();
};

#endif
