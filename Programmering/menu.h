#ifndef MENU_H
#define MENU_H
#include <stdio.h>

typedef struct{
  char title[16];
  char menu1[16];
  char menu2[16];
  char menu3[16];
} MENU;

typedef struct Node {
  MENU menu;
  struct Node* parent;
  struct Node* child1;
  struct Node* child2;
  struct Node* child3;
} Node;


Node newNode(MENU menu);
void initMenu(void);

#endif
