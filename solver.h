#ifndef SOLVER_H
#define SOLVER_H

#include <set>
#include <string>

#include <ncurses.h>  // add library

using namespace std; // add this

class Solver {
private:
	int psbl;

    int tries;
    int len;
    int base;
    int bulls;
    int cows;
    int ans;
    std::set<int> posNums;
	
	int global_status;
	
	int schet;
	
    void delNums(int num);
    bool checkNum(int num, int ans, std::set<int>& filt);
    int guessNum();
    int handleInput(WINDOW *win);
    bool is_number(std::string& s);

public:
    int newGame(int psbl_);
	int newGame(int zeleboba, int psbl_);

    void initNums(int length);

    //int guessNum(int psbl);
	int continue_game ();
};

#endif