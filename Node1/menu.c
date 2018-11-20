#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <avr/pgmspace.h>
#include "F_CPU.h"
#include "util/delay.h"
#include "oled.h"
#include "joystick.h"
#include "menu.h"
#include "menu_names.h"
#include "sram.h"


Node newNode(MENU menu){
  // Assign struct to Node
  Node node;
  node.menu = menu;

  // Parent and children
  node.parent = NULL;
  node.child1 = NULL;
  node.child2 = NULL;
  node.child3 = NULL;

  return node;
}


void initMenu(void){
  oled_init();
  oled_clearScreen();   // Clear screen, go to pos (0, 0)
  _delay_ms(500);
  // Making the Main Menu struct
  MENU MainMenu;

  // Main menu interface
  MainMenu.title = MM_title_string;
  MainMenu.menu1 = MM_menu1_string;
  MainMenu.menu2 = MM_menu2_string;
  MainMenu.menu3 = MM_menu3_string;

  // Sub Menus
  MENU PlayGame;
  MENU HighScores;
  MENU Settings;

  // Play Game interface
  PlayGame.title = PG_title_string;
  PlayGame.menu1 = PG_menu1_string;
  PlayGame.menu2 = PG_menu2_string;
  PlayGame.menu3 = PG_menu3_string;

  // High Scores interface
  HighScores.title = HS_title_string;
  char HS1[16], HS2[16], HS3[16];

  uint8_t HIGHSCORES[3];
  SRAM_read_highscores(&HIGHSCORES[0]);

  // Converting uint8_t to string
  itoa(HIGHSCORES[0], HS1, 10);
  itoa(HIGHSCORES[1], HS2, 10);
  itoa(HIGHSCORES[2], HS3, 10);

  HighScores.menu1 = HS3;
  HighScores.menu2 = HS2;
  HighScores.menu3 = HS1;

  // Settings interface
  Settings.title = SETTING_title_string;
  Settings.menu1 = SETTING_menu1_string;
  Settings.menu2 = SETTING_menu2_string;
  Settings.menu3 = SETTING_menu3_string;

  // Initialize main menu
  mainMenuNode   = newNode(MainMenu);
  playGameNode   = newNode(PlayGame);
  highScoresNode = newNode(HighScores);
  settingsNode   = newNode(Settings);

  // Addressen til mainMenu.child1 blir satt til addressen settings
  mainMenuNode.child1 = &playGameNode;
  mainMenuNode.child2 = &highScoresNode;
  mainMenuNode.child3 = &settingsNode;

  playGameNode.parent = &mainMenuNode;
  highScoresNode.parent = &mainMenuNode;
  settingsNode.parent = &mainMenuNode;

  // Making Main Menu
  constructMenu(&mainMenuNode);
}


void constructMenu(Node* node){
  // Initialize screen
  oled_clearScreen();
  currentNode = node;
  arrowPagePos = 2;
  setArrow(arrowPagePos);

  // Construct menu
  oled_pos(0,10);
  oled_print(node->menu.title);
  oled_pos(2,20);
  oled_print(node->menu.menu1);
  oled_pos(3,20);
  oled_print(node->menu.menu2);
  oled_pos(4,20);
  oled_print(node->menu.menu3);
  _delay_ms(500);
}


void removeArrow(int line){
  oled_pos(line, 0);
  for(int i = 0; i < 8*strlen(Arrow_string); i++){
    oled_write_data(0x00);
  }
}


void setArrow(int line){
  if(line < 5 && line > 1){
    removeArrow(arrowPagePos);
    oled_pos(line, 0);
    oled_print(Arrow_string);
    arrowPagePos = line;
  }
  _delay_ms(300); // Such that the user have time to put joystick to neutral
}


const char* update_menu(){
  JOY_dir_t joyDirection = getJoystickDirection(50);
  if(joyDirection == UP){
    setArrow(arrowPagePos-1);
  }
  if(joyDirection == DOWN){
    setArrow(arrowPagePos+1);
  }
  if(joyDirection == LEFT && currentNode->parent != NULL){
    constructMenu(currentNode->parent);
  }
  if(joyDirection == RIGHT){
    switch(arrowPagePos){
      case 2:
        if(currentNode->child1 != NULL){
          constructMenu(currentNode->child1);
        }else if ( strcmp(currentNode->menu.menu1, "Easy") == 0 ){
          return currentNode->menu.menu1;
        }
        break;
      case 3:
        if(currentNode->child2 != NULL){
          constructMenu(currentNode->child2);
        }else if ( strcmp(currentNode->menu.menu2, "Medium") == 0 ){
          return currentNode->menu.menu2;
        }
        break;
      case 4:
        if(currentNode->child3 != NULL){
          constructMenu(currentNode->child3);
        }else if ( strcmp(currentNode->menu.menu3, "Hard") == 0 ){
          return currentNode->menu.menu3;
        }
        break;
      default: break;
    }
  }
  return NULL;
}
