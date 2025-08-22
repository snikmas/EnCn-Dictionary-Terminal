#include "main.h"

int main(void){

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  refresh();

  welcomePage(); // completed.

  int choice = menuPage();

  printf("%i choice", choice);


  endwin();

  return 0;

}