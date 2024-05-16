#include <ncurses.h>
#include <iostream>
#include <string>
#include "host.h"
#include "menu.h"

using namespace std;

void StartVisual() {
        initscr();
        curs_set(0);
        keypad(stdscr, TRUE);
        nodelay(stdscr, TRUE);
        nonl();
        cbreak();
        noecho();
}

void ExitProgram(const char *message, int ans) {
    endwin();
    std::cout << message << std::endl;
    exit(ans);
}

int main() {

    StartVisual();
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    if (yMax < 35 || xMax < 30) {
            ExitProgram("Your terminal must be at least 35 rows and 30 coloms to play game", -1);
    }

    int win_width, win_height;
    win_height = 32;
    win_width = 28;
    menu m(win_height, win_width);
    
    m.start();
    ExitProgram("", 0);
    return 0;
}