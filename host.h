#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>

#include <ncurses.h> // add library

using namespace std;  // add this

class Host {
private:
    vector<char> num;
    int len;
    int base;

	int global_status;

    bool initNumber(int length, int uBase, WINDOW *win);
	bool initNumber(int length);
    int handleInput(string input, WINDOW *win, WINDOW *win_cow);
    bool checkNumber(vector<char>& digits, WINDOW *win);
    bool is_number(std::string& s);

public:
    int newGame();
	int newGame(int zeleboba);
	int continue_game();
};

#endif