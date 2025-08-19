#include <ncurses.h>
#include <string.h>
#include <unistd.h>

char *welcome_title = "WELCOME TO TERMINAL";
char *mascot[] = {
    "   (\\_._/)",
    "   ( •‿• )   System Online.",
    "   /  V  \\   Dictionary Booting...",
    "  /(  -  )\\",
    "   ^^   ^^"
};
int mascot_lines = sizeof(mascot) / sizeof(mascot[0]);

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    int menuWidth = 50;

    // Title Window
    WINDOW *titleWin = newwin(3, menuWidth, 0, (xMax - menuWidth) / 2);
    box(titleWin, 0, 0);
    mvwprintw(titleWin, 1, (menuWidth - strlen(welcome_title)) / 2, "%s", welcome_title);
    wrefresh(titleWin);

    // Mascot Window
    WINDOW *mascotWin = newwin(mascot_lines + 2, menuWidth, 4, (xMax - menuWidth) / 2);
    box(mascotWin, 0, 0);
    for (int i = 0; i < mascot_lines; i++) {
        mvwprintw(mascotWin, i + 1, 2, "%s", mascot[i]);
        wrefresh(mascotWin);
        usleep(150000); // little animation effect
    }

    // Message Window
    WINDOW *msgWin = newwin(3, menuWidth, 4 + mascot_lines + 3, (xMax - menuWidth) / 2);
    box(msgWin, 0, 0);
    char *msg = "Please wait while we prepare your session...";
    mvwprintw(msgWin, 1, (menuWidth - strlen(msg)) / 2, "%s", msg);
    wrefresh(msgWin);

    // Input Window (like your example)
    WINDOW *inputWin = newwin(3, menuWidth, yMax - 4, (xMax - menuWidth) / 2);
    box(inputWin, 0, ' ');
    mvwprintw(inputWin, 1, 2, "Enter your command:");
    wrefresh(inputWin);

    char input[100];
    echo();
    curs_set(1);
    wgetnstr(inputWin, input, sizeof(input) - 1);

    // Result Window
    noecho();
    curs_set(0);
    WINDOW *resultWin = newwin(4, menuWidth, yMax - 8, (xMax - menuWidth) / 2);
    box(resultWin, 0, 0);
    mvwprintw(resultWin, 1, 2, "Input: %s", input);
    mvwprintw(resultWin, 2, 2, "Translation: <demo>");
    wrefresh(resultWin);

    getch();
    endwin();
    return 0;
}
