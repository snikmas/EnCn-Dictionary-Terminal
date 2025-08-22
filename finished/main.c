#include "ascii.h"

int main(void){

  initscr();
  noecho();
  cbreak();
  curs_set(0);
  refresh();

  welcomePage();

  menuPage();



  endwinO();

  return 0;

}