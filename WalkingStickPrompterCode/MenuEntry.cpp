#include "MenuEntry.h"

MenuEntry::MenuEntry(){
}

MenuEntry::MenuEntry(int idIn, String labelIn){
    id = idIn;
    label = labelIn;
    parent = NULL;
    subEntries = NULL;
}
    
MenuEntry::MenuEntry(int idIn, String labelIn, Array<MenuEntry, MAX_NUM_MENU_ENTRIES> &subEntriesIn){
    MenuEntry(idIn, labelIn);
}
    
int MenuEntry::getId(){
    return id;
}
    
String MenuEntry::getLabel(){
    return label;
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
