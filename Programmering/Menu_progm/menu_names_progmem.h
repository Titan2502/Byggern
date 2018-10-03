#ifndef MENU_NAME_H
#define MENU_NAME_H
#include <stdio.h>
#include <avr/pgmspace.h>

// ---- Main Menu ----
const char PROGMEM MM_title_string[]  = "Main Menu";
const char PROGMEM MM_menu1_string[]  = "Play Game";
const char PROGMEM MM_menu2_string[]  = "High Scores";
const char PROGMEM MM_menu3_string[]  = "Settings";

// ---- Sub Menus ----
// MENU PlayGame;
const char PROGMEM PG_title_string[]  = "Empty";
const char PROGMEM PG_menu1_string[]  = "Empty";
const char PROGMEM PG_menu2_string[]  = "Empty";
const char PROGMEM PG_menu3_string[]  = "Empty";

// MENU HighScores;
const char PROGMEM HS_title_string[]  = "Empty";
const char PROGMEM HS_menu1_string[]  = "Empty";
const char PROGMEM HS_menu2_string[]  = "Empty";
const char PROGMEM HS_menu3_string[]  = "Empty";

// MENU Settings;
const char PROGMEM SETTING_title_string[]  = "Settings";
const char PROGMEM SETTING_menu1_string[]  = "Sensitivity";
const char PROGMEM SETTING_menu2_string[]  = "Brightness";
const char PROGMEM SETTING_menu3_string[]  = "Awesomeness";

#endif
