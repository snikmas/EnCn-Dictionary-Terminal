#include "ascii.h"
#include "word.h"
#include "main.h"

void actions(char *source, int mode, Word *newWord){

  noecho();
  cbreak();
  curs_set(0);




  if(strcmp(source, "translateMode")){
    return
  } else if (strcmp(source, "historyAction")) {
    return
  } else if(strcmp(source, "savedActoin")){
    return;
  } else if (strcmp(source, "onlyMenuBack")){
    return ;
  }
}