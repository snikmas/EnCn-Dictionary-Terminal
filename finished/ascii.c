#include "ascii.h"
#include "main.h"

// CONTENT: titles, menus, mascots

const char *page_titles[3] = {
    "EN - CN Dictionary",
    "CN - EN Dictionary",
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


const char *const *menus[3] = {
    menu_1, menu_2, menu_3,
};
// ALL MASCOTS

static char *mascot0[] = {
    "        (\\_._/)                        ",
    "        ( o o )   System Online.        ",
    "        /  V  \\   Dictionary Booting... ",
    "       /(  _  )\\                        ",
    "         ^^ ^^                          "
};

static char *mascot1[] = {
    "        (\\_._/)                        ",
    "        ( ^ ^ )      Welcome, Hacker.   ",
    "        /  V  \\      Terminal Ready.    ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot2[] = {
    "        (\\_._/)                        ",
    "        ( ^ ^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot3[] = {
    "        (\\_._/)                        ",
    "        ( - - )                        ",
    "        /  z  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot4[] = {
    "        (\\_._/)                        ",
    "        ( > < )                        ",
    "        /  V  \\                        ",
    "       /(  U  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot5[] = {
    "        (\\_._/)                        ",
    "        ( ^_^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot6[] = {
    "        (\\_._/)                        ",
    "        ( o_o )                        ",
    "        /  O  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot7[] = {
    "        (\\_._/)                        ",
    "        ( T T )                        ",
    "        /  ~  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot8[] = {
    "        (\\_._/)                        ",
    "        ( ^o^ )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot9[] = {
    "        (\\_._/)                        ",
    "        ( >_> )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

static char *mascot10[] = {
    "        (\\_._/)                        ",
    "        ( -_- )                        ",
    "        /  V  \\                        ",
    "       /(  _  )\\                        ",
    "        ^^   ^^                          "
};

const char *const *mascots[NUM_MASCOTS] = {
    mascot0, mascot1, mascot2, mascot3, mascot4,
    mascot5, mascot6, mascot7, mascot8, mascot9,
    mascot10
};
