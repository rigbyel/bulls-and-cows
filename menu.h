#ifndef MENU_H
#define MENU_H

#include <ncurses.h>
#include <string>
#include <vector>
#include "host.h"

using namespace std;

class menu
{
private:
    WINDOW *menuwin;
    int _height, _width;
    int y_max, x_max;
    Host h;

    vector<string> choices = {"Solve", "Host", "Compete", "Help", "Exit"};
    vector<string> levs = {"Easy", "Medium", "Hard", "Impossible"};

public:
    menu(int height, int width);
    void clean();
    int main_menu();
    int start();
    int levels();
    void stop();
    int solveGame();
    string getstring(int* ypos, int* xpos);
    int handleInput(string input);
};


#endif