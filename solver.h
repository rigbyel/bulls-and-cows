#ifndef SOLVER_H
#define SOLVER_H

#include <set>
#include <string>


class Solver {
private:
    int tries;
    int len;
    int base;
    int bulls;
    int cows;
    int ans;
    std::set<int> posNums;

    void delNums(int num);
    bool checkNum(int num, int ans, std::set<int>& filt);
    int guessNum();
    int handleInput();
    void initNums(int length);
    bool is_number(std::string& s);

public:
    int newGame();
};

#endif