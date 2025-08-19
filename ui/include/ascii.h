#ifdef ASCII_H
#define ASCII_H

#include <ncurses.h>
#include <string.h>
#include <unistd.h>


// welcome page
void draw_loading(WINDOW *win, int y, int x, int width, int percent);
void welcomePage();

// menu
int menuPage();
char *menus_items[];
int items;
char *mascot[];
int mascot_lines;




#endif ASCII_H