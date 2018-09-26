#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include "util/delay.h"
#include "F_CPU.h"
#include "oled.h"
#include "joystick.h"
#include "menu.h"
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
  strcpy( MainMenu.title,  "Main Menu");
  strcpy( MainMenu.menu1,  "Play Game");
  strcpy( MainMenu.menu2,  "High Scores");
  strcpy( MainMenu.menu3,  "Settings");


  // Sub Menus
  MENU PlayGame;
  MENU HighScores;
  MENU Settings;

  // Play Game interface
  strcpy( PlayGame.title,  "Empty");
  strcpy( PlayGame.menu1,  "Empty");
  strcpy( PlayGame.menu2,  "Empty");
  strcpy( PlayGame.menu3,  "Empty");

  // High Scores interface
  strcpy( HighScores.title,  "Empty");
  strcpy( HighScores.menu1,  "Empty");
  strcpy( HighScores.menu2,  "Empty");
  strcpy( HighScores.menu3,  "Empty");

  // Settings interface
  strcpy( Settings.title,  "Settings");
  strcpy( Settings.menu1,  "Sensitivity");
  strcpy( Settings.menu2,  "Brightness");
  strcpy( Settings.menu3,  "Awesomeness");

  // Initialize main menu
  Node mainMenuNode   = newNode(MainMenu);
  Node playGameNode   = newNode(PlayGame);
  Node highScoresNode = newNode(HighScores);
  Node settingsNode   = newNode(Settings);


  // Addressen til mainMenu.child1 blir satt til addressen settings
  mainMenuNode.child1 = &PlayGame;
  mainMenuNode.child2 = &HighScores;
  // mainMenuNode.child3 = &settingsNode;
  //
  //
  // printf(mainMenuNode.child2->menu.menu1);




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
