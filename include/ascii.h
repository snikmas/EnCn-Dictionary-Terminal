#ifndef ASCII_H
#define ASCII_H

#include <ncurses.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ncurses.h>
#include <stdlib.h>
#include <ctype.h>

// welcome page
void draw_loading(WINDOW *win, int y, int x, int width, int percent);
void welcomePage();

// menu
int menuPage();
extern char *menus_items[];
extern int items;





#endif 