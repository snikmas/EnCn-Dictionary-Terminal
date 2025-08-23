#include "word.h"
#include "ascii.h"
#include "main.h"

// Global variable definitions
struct NodeWord *HEAD_HISTORY = NULL;
struct NodeWord *TAIL_HISTORY = NULL;
struct NodeWord *HEAD_FAV = NULL;
struct NodeWord *TAIL_FAV = NULL;

void addToHistory(Word *newWord) {
  if (!newWord || !newWord->wordEn || !newWord->wordCn) {
    return; // Don't save invalid words
  }
  
  // Create a new node
  struct NodeWord *newNode = malloc(sizeof(struct NodeWord));
  if (!newNode) {
    return; // Memory allocation failed
  }
  
  // Create a copy of the word
  Word *wordCopy = malloc(sizeof(Word));
  if (!wordCopy) {
    free(newNode);
    return;
  }
  
  // Copy the word data
  wordCopy->wordEn = strdup(newWord->wordEn);
  wordCopy->wordCn = strdup(newWord->wordCn);
  wordCopy->isFavorite = false;
  
  if (!wordCopy->wordEn || !wordCopy->wordCn) {
    // String duplication failed
    if (wordCopy->wordEn) free(wordCopy->wordEn);
    if (wordCopy->wordCn) free(wordCopy->wordCn);
    free(wordCopy);
    free(newNode);
    return;
  }
  
  // Link the node
  newNode->word = wordCopy;
  newNode->next = NULL;
  
  // Add to the beginning of the list
  if (HEAD_HISTORY == NULL) {
    HEAD_HISTORY = newNode;
    TAIL_HISTORY = newNode;
  } else {
    newNode->next = HEAD_HISTORY;
    HEAD_HISTORY = newNode;
  }
}

void addSavedWord(Word *newWord){
  if (!newWord || !newWord->wordEn || !newWord->wordCn) {
    return; // Don't save invalid words
  }
  
  // Create a new node
  struct NodeWord *newNode = malloc(sizeof(struct NodeWord));
  if (!newNode) {
    return; // Memory allocation failed
  }
  
  // Create a copy of the word
  Word *wordCopy = malloc(sizeof(Word));
  if (!wordCopy) {
    free(newNode);
    return;
  }
  
  // Copy the word data
  wordCopy->wordEn = strdup(newWord->wordEn);
  wordCopy->wordCn = strdup(newWord->wordCn);
  wordCopy->isFavorite = true;
  
  if (!wordCopy->wordEn || !wordCopy->wordCn) {
    // String duplication failed
    if (wordCopy->wordEn) free(wordCopy->wordEn);
    if (wordCopy->wordCn) free(wordCopy->wordCn);
    free(wordCopy);
    free(newNode);
    return;
  }
  
  // Link the node
  newNode->word = wordCopy;
  newNode->next = NULL;
  
  // Add to the beginning of the list
  if (HEAD_FAV == NULL) {
    HEAD_FAV = newNode;
    TAIL_FAV = newNode;
  } else {
    newNode->next = HEAD_FAV;
    HEAD_FAV = newNode;
  }
}

void saved_operations(Word *newWord, char operation){
  if (operation == 'r') {
    // Delete a word (remove first word for now)
    if (HEAD_FAV != NULL) {
      struct NodeWord *temp = HEAD_FAV;
      HEAD_FAV = HEAD_FAV->next;
      
      if (temp->word) {
        if (temp->word->wordEn) free(temp->word->wordEn);
        if (temp->word->wordCn) free(temp->word->wordCn);
        free(temp->word);
      }
      free(temp);
      
      if (HEAD_FAV == NULL) {
        TAIL_FAV = NULL;
      }
    }
  } else if (operation == 'R') {
    // Clear all saved words
    struct NodeWord *current = HEAD_FAV;
    while (current != NULL) {
      struct NodeWord *temp = current;
      current = current->next;
      
      if (temp->word) {
        if (temp->word->wordEn) free(temp->word->wordEn);
        if (temp->word->wordCn) free(temp->word->wordCn);
        free(temp->word);
      }
      free(temp);
    }
    HEAD_FAV = NULL;
    TAIL_FAV = NULL;
  }
}

void viewSaved() {
    clear();
    refresh();
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int startX = (xMax - PROGRAM_WIDTH) / 2;
    if (startX < 0) startX = 0;
    
    // Title Window
    WINDOW *titleWin = newwin(3, PROGRAM_WIDTH, 1, startX);
    if (!titleWin) return;
    
    // Draw box manually
    box(titleWin, 0, 0);
    
    mvwprintw(titleWin, 1, (PROGRAM_WIDTH - strlen("Saved Words")) / 2, "Saved Words");
    wrefresh(titleWin);
    
    // Content Window
    WINDOW *contentWin = newwin(15, PROGRAM_WIDTH, 5, startX);
    if (!contentWin) {
        delwin(titleWin);
        return;
    }
    
    // Draw box manually
    box(contentWin, 0, 0);
    
    if (HEAD_FAV == NULL) {
        mvwprintw(contentWin, 2, 2, "No saved words yet.");
        mvwprintw(contentWin, 4, 2, "Press any key to return to main menu...");
    } else {
        mvwprintw(contentWin, 1, 2, "Your saved words:");
        mvwprintw(contentWin, 2, 2, "==================");
        
        struct NodeWord *current = HEAD_FAV;
        int line = 3;
        int count = 0;
        
        while (current != NULL && line < 12) {
            if (current->word && current->word->wordEn && current->word->wordCn) {
                mvwprintw(contentWin, line, 2, "%d. %s -> %s", 
                          count + 1, 
                          current->word->wordEn, 
                          current->word->wordCn);
                line++;
                count++;
            }
            current = current->next;
        }
        
        if (current != NULL) {
            mvwprintw(contentWin, line, 2, "... and %d more words", count);
            line++;
        }
    }
    
    wrefresh(contentWin);
    
    // Cleanup content window before showing action menu
    delwin(titleWin);
    delwin(contentWin);
    
    // Show action menu at the bottom
    actions("savedAction", -1, NULL, 20);
}

void viewHistory() {
    clear();
    refresh();
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int startX = (xMax - PROGRAM_WIDTH) / 2;
    if (startX < 0) startX = 0;
    
    // Title Window
    WINDOW *titleWin = newwin(3, PROGRAM_WIDTH, 1, startX);
    if (!titleWin) return;
    
    // Draw box manually
    int titleHeight, titleWidth;
    getmaxyx(titleWin, titleHeight, titleWidth);
    mvwaddch(titleWin, 0, 0, ACS_ULCORNER);
    mvwaddch(titleWin, 0, titleWidth-1, ACS_URCORNER);
    mvwaddch(titleWin, titleHeight-1, 0, ACS_LLCORNER);
    mvwaddch(titleWin, titleHeight-1, titleWidth-1, ACS_LRCORNER);
    mvwhline(titleWin, 0, 1, ACS_HLINE, titleWidth-2);
    mvwhline(titleWin, titleHeight-1, 1, ACS_HLINE, titleWidth-2);
    mvwvline(titleWin, 1, 0, ACS_VLINE, titleHeight-2);
    mvwvline(titleWin, 1, titleWidth-1, ACS_VLINE, titleHeight-2);
    
    mvwprintw(titleWin, 1, (PROGRAM_WIDTH - strlen("Translation History")) / 2, "Translation History");
    wrefresh(titleWin);
    
    // Content Window
    WINDOW *contentWin = newwin(15, PROGRAM_WIDTH, 5, startX);
    if (!contentWin) {
        delwin(titleWin);
        return;
    }
    
    // Draw box manually
    box(contentWin, 0, 0);
    
    if (HEAD_HISTORY == NULL) {
        mvwprintw(contentWin, 2, 2, "No translation history yet.");
        mvwprintw(contentWin, 4, 2, "Press any key to return to main menu...");
    } else {
        mvwprintw(contentWin, 1, 2, "Your translation history:");
        mvwprintw(contentWin, 2, 2, "=========================");
        
        struct NodeWord *current = HEAD_HISTORY;
        int line = 3;
        int count = 0;
        
        while (current != NULL && line < 12) {
            if (current->word && current->word->wordEn && current->word->wordCn) {
                mvwprintw(contentWin, line, 2, "%d. %s -> %s", 
                          count + 1, 
                          current->word->wordEn, 
                          current->word->wordCn);
                line++;
                count++;
            }
            current = current->next;
        }
        
        if (current != NULL) {
            mvwprintw(contentWin, line, 2, "... and %d more translations", count);
            line++;
        }
    }
    
    wrefresh(contentWin);
    
    // Cleanup content window before showing action menu
    delwin(titleWin);
    delwin(contentWin);
    
    // Show action menu at the bottom
    actions("historyAction", -1, NULL, 20);
}