#include <ncurses.h>

int main(){

  // NOT PIXELS -> LINES! WE USE CURSOR
  initscr();

  const width = 120;
  const height = 35;
  int height, width, start_y, start_x;
  height = 10;
  width = 20;
  start_x = start_y = 10;
  
  WINDOW *win = newwin(height, width, start_y, start_x);
  refresh(); //1. we created a window
  
  // border
  box(win, 0, 0 );
  mvwprintw(win, 1, 1, "this is my booox\n");  // writting in the our window box
  wrefresh(win); // 2. resfresh our window
  // we use "imaginary" cursor: we do move -> and a cursor change the place

  // move the cursor to the specified location
  int x, y;
  x = y = 10;
  move(y, x);
  refresh();

  // prints a string(const char*)  to a window = printf
  // printw("hiiiiiii");

  // mvprintw(10, 1, "go");

  // clear(); 

  // refreshes the screen to match whats in memory
  // refresh();

  move(0, 0);
  // whats for user input returns int value of that key
  int c = getch();
  printw("%d", c);

  getch();


  
  endwin();


  return 0;
}