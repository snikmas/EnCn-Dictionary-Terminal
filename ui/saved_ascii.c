#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include "saved.h"
#include "actions.h"

struct NodeWord *HEAD_SAVED = NULL;
struct NodeWord *TAIL_SAVED = NULL;

char *menus_items_saved[] = {
    "SAVINGS LOG"
};

int menuWidth_saved = 50;

void viewSaved() {
    clear();
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    int startX = (xMax - menuWidth_saved) / 2;
    int startY = 2;

    WINDOW *win = newwin(yMax - 4, menuWidth_saved, startY, startX);
    box(win, 0, 0);
    mvwprintw(win, 1, 2, "%s", menus_items_saved[0]);

    int line = 3;
    if (HEAD_SAVED != NULL) {
        int count = 1;
        for (struct NodeWord *i = HEAD_SAVED; i != NULL; i = i->next) {
            mvwprintw(win, line++, 2, "[%i] %s -> %s", count++, i->word->wordEn, i->word->wordCn);
        }
    } else {
        mvwprintw(win, line++, 2, "No savings available.");
        mvwprintw(win, line++, 2, "Tip: NO TIPS.");
        wrefresh(win);
        actions("onlyMenuBack", -1, NULL);
        delwin(win);
        return;
    }

    wrefresh(win);
    actions("savedAction", -1, NULL);
    delwin(win);
}

void addSavedWord(Word *newWord) {
    struct NodeWord *newNode = malloc(sizeof(struct NodeWord));
    if (!newNode) handleErrors(ERR_OUT_OF_MEMORY, "addSavedWord");

    newNode->word = newWord;
    newNode->next = NULL;

    if (HEAD_SAVED == NULL) {
        HEAD_SAVED = newNode;
        TAIL_SAVED = newNode;
    } else {
        TAIL_SAVED->next = newNode;
        TAIL_SAVED = newNode;
    }

    printw("The word was added!\n");
    refresh();
}

void deleteSavedEntry() {
    int number = -1;
    printw("Input the number of the word to delete:\n>> ");
    refresh();

    while (1) {
        scanw("%d", &number);
        if (number < 1) {
            printw("Invalid Input! Try again:\n>> ");
            refresh();
            continue;
        }
        break;
    }

    NodeWord *current = HEAD_SAVED;
    NodeWord *prev = NULL;

    for (int i = 1; i < number && current != NULL; i++) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printw("Position out of bounds!\n");
        refresh();
        viewSaved();
        return;
    }

    if (prev == NULL) {
        HEAD_SAVED = current->next;
        if (HEAD_SAVED == NULL) TAIL_SAVED = NULL;
    } else {
        prev->next = current->next;
        if (current == TAIL_SAVED) TAIL_SAVED = prev;
    }

    free(current->word);
    free(current);

    printw("The word was successfully deleted!\n");
    refresh();
    viewSaved();
}

void deleteSaved() {
    int choice = -1;
    printw("Are you sure you want to clear all savings?\n[1] Yes\n[0] No\n>> ");
    refresh();

    while (1) {
        scanw("%d", &choice);
        if (choice < 0 || choice > 1) {
            printw("Invalid Input. Please, try again:\n>> ");
            refresh();
            continue;
        }
        break;
    }

    if (choice == 0) {
        viewSaved();
        return;
    }

    NodeWord *current = HEAD_SAVED;
    while (current != NULL) {
        NodeWord *temp = current->next;
        free(current->word);
        free(current);
        current = temp;
    }

    HEAD_SAVED = NULL;
    TAIL_SAVED = NULL;

    printw("All savings were deleted.\n");
    refresh();
    viewSaved();
}

void saved_operations(Word *newWord, char operation) {
    switch (operation) {
        case 'R': deleteSaved(); break;
        case 'r': deleteSavedEntry(); break;
        case 'a': addSavedWord(newWord); break;
    }
}
