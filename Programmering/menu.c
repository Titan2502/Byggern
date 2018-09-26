#include <avr/io.h>
#include <stdlib.h>
#include "util/delay.h"
#include "F_CPU.h"
#include "oled.h"
#include "joystick.h"
#include "menu.h"
#include "menu_names.h"

// ---- Joystick function ---- //
// JOY_pos getJoystickAnalogPos(void);
//
// SLIDER_pos getSliderAnalogPos(void);
//
// JOY_dir_t getJoystickDirection(int deadzone);

Node newNode(MENU menu){
  // Assign struct to Node
  Node node;
  node.menu = menu;

  // Parent and children
  node.parent = NULL;
  node.child1 = NULL;
  node.child2 = NULL;
  node.child3 = NULL;

  return(node);
}


void initMenu(void){
  oled_init();
  oled_clearScreen();   // Clear screen, go to pos (0, 0)
  // Making the Main Menu struct
  MENU MainMenu;

  // Main menu interface
  MainMenu.title = &MM_title_string;
  MainMenu.menu1 = &MM_menu1_string;
  MainMenu.menu2 = &MM_menu2_string;
  MainMenu.menu3 = &MM_menu3_string;


  // Sub Menus
  MENU PlayGame;
  MENU HighScores;
  MENU Settings;

  printf("Hello1");
  // Play Game interface
  MainMenu.title = &PG_title_string;
  MainMenu.menu1 = &PG_menu1_string;
  MainMenu.menu2 = &PG_menu2_string;
  MainMenu.menu3 = &PG_menu3_string;

  // High Scores interface
  MainMenu.title = &HS_title_string;
  MainMenu.menu1 = &HS_menu1_string;
  MainMenu.menu2 = &HS_menu2_string;
  MainMenu.menu3 = &HS_menu3_string;

  // Settings interface
  MainMenu.title = &SETTING_title_string;
  MainMenu.menu1 = &SETTING_menu1_string;
  MainMenu.menu2 = &SETTING_menu1_string;
  MainMenu.menu3 = &SETTING_menu1_string;

  printf("Hello2");
  // Initialize main menu
  Node mainMenuNode   = newNode(MainMenu);
  Node playGameNode   = newNode(PlayGame);
  Node highScoresNode = newNode(HighScores);
  Node settingsNode   = newNode(Settings);


  // Addressen til mainMenu.child1 blir satt til addressen settings
  mainMenuNode.child1 = &playGameNode;
  mainMenuNode.child2 = &highScoresNode;
  mainMenuNode.child3 = &settingsNode;

  playGameNode.parent = &mainMenuNode;
  settingsNode.parent = &mainMenuNode;

  printf("Hello3");
  printf(mainMenuNode.child1->menu.menu1);




  // char mainMenu_title[] = "Main Menu";
  // char *mmpointer = &mainMenu_title[0];
  // char home[] = "Settings";
  //
  // char settings[] = "  Settings";
  // char *settingPointer = &settings[0];
  //
  // char pointer[] = "->";
  // char *ppointer = &pointer[0];
  //
  // oled_pos(0, 20);
  // oled_print(mmpointer);
  //
  // oled_pos(2, 16);
  // oled_print(settingPointer);
  //
  // oled_pos(2, 0);
  // oled_print(ppointer);

}
