#include "MenuEntry.h"

MenuEntry::MenuEntry(){
}

MenuEntry::MenuEntry(int idIn, char* labelIn, bool clearDataOnDestructIn){
    id = idIn;
    label = labelIn;
    parent = NULL;
    subEntries = NULL;
    clearDataOnDestruct = clearDataOnDestructIn;
}


MenuEntry::MenuEntry(int idIn, char* labelIn){
    MenuEntry(idIn, labelIn, clearDataOnDestruct);
}
    
MenuEntry::MenuEntry(int idIn, char* labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn, bool clearDataOnDestructIn){
    MenuEntry(idIn, labelIn, clearDataOnDestructIn);
}
    
MenuEntry::MenuEntry(int idIn, char* labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn){
    MenuEntry(idIn, labelIn);
}
    
int MenuEntry::getId(){
    return id;
}
    
char* MenuEntry::getLabel(){
    return label;
}
    
char* MenuEntry::getLabelCopy(){
    char* labelCpy = new char[sizeof(label)];
    strcpy(labelCpy, label);
    return labelCpy;
}
    
MenuEntry* MenuEntry::getParent(){
    return parent;
}
    
bool MenuEntry::hasParent(){
    return getParent() != NULL;
}
    
Array<MenuEntry, MAX_NUM_MENU_ENTRIES>* MenuEntry::getSubEntries(){
    return subEntries;
}
    
bool MenuEntry::hasSubEntries(){
    return getSubEntries() != NULL;
}

MenuEntry::~MenuEntry(){
    if(!clearDataOnDestruct){
    	return;
    }
    delete[] label;
    if(subEntries != NULL){
    	//todo:: iterate through sub entries, delete
    }
}
