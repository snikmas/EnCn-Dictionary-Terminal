#include "headers/ascii.h"
#include "headers/main.h"

// CONTENT: titles, menus, mascots

const char *page_titles[5] = {
    "EN - CN Dictionary",
    "EN - CN Mode", // default[1]
    "CN - EN Mode",
    "Saved",
    "History Log",
};

// actions menu 
static const char *action_menu_translate[] = {
    "[*] Save the word",
    "[1] Translate another word",
    "[2] Back to main menu",
    NULL
};

static const char *action_menu_history[] = {
    "[1] Delete an entry",
    "[2] Clear all history",
    "[0] Back to main menu",
    NULL
};

static const char *action_menu_saved[] = {
    "[1] Delete an entry",
    "[2] Clear all saved words",
    "[0] Back to main menu",
    NULL
};

static const char *action_menu_back[] = {
    "[0] Back to main menu",
    NULL
};

// Master table of all action menus
const char **action_menus[] = {
    action_menu_translate,
    action_menu_history,
    action_menu_saved,
    action_menu_back
};


// MENU_PAGE

static char *menu_1[] = {
    "[1] Translate EN -> CN",
    "[2] Translate CN -> EN",
    "[3] Saved Translations",
    "[4] History",
    "[0] Exit",
};


static char *menu_2[] = {
    "[1] Save a word",
    "[2] Translate another word",
    "[3] Back to main menu",
};

static char *menu_3[] = {
    "[1] Delete a word",
    "[2] Clear all savings",
    "[3] Back to main menu",
};


const char **menus[3] = {
    menu_1, menu_2, menu_3,
};
// ALL MASCOTS

static const char *mascot0[] = {
    "        (\\_._/)                        ",
    "        ( o o )   System Online.        ",
    "        /  V  \\   Dictionary Booting... ",
    "       /(  _  )\\                        ",
    "         ^^ ^^                          "
};

static const char *mascot1[] = {
    "        (\\_._/)                        ",
    "        ( ^ ^ )      Welcome, Hacker.   ",
    "        /  V  \\      Terminal Ready.    ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot2[] = {
    "        (\\_._/)                        ",
    "        ( ^ ^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot3[] = {
    "        (\\_._/)                        ",
    "        ( - - )                        ",
    "        /  z  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot4[] = {
    "        (\\_._/)                        ",
    "        ( > < )                        ",
    "        /  V  \\                        ",
    "       /(  U  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot5[] = {
    "        (\\_._/)                        ",
    "        ( ^_^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot6[] = {
    "        (\\_._/)                        ",
    "        ( o_o )                        ",
    "        /  O  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot7[] = {
    "        (\\_._/)                        ",
    "        ( T T )                        ",
    "        /  ~  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot8[] = {
    "        (\\_._/)                        ",
    "        ( ^o^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot9[] = {
    "        (\\_._/)                        ",
    "        ( >_> )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static const char *mascot10[] = {
    "        (\\_._/)                        ",
    "        ( -_- )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

const char **mascots[NUM_MASCOTS] = {
    mascot0, mascot1, mascot2, mascot3, mascot4,
    mascot5, mascot6, mascot7, mascot8, mascot9,
    mascot10
};
