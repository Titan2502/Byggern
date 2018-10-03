#ifndef MENU_H
#define MENU_H
#include <stdio.h>

typedef struct{
  const char* title;
  const char* menu1;
  const char* menu2;
  const char* menu3;
} MENU;

typedef struct Node {
  MENU menu;
  struct Node* parent;
  struct Node* child1;
  struct Node* child2;
  struct Node* child3;
} Node;


void initMenu(void);
void constructMenu(Node* currentNode);
void removeArrow(int line);
void setArrow(int line);
void checkJoystickDirection(void);


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

uint8_t arrowPagePos;
Node* currentNode;
Node mainMenuNode;
Node playGameNode;
Node highScoresNode;
Node settingsNode;

#endif
