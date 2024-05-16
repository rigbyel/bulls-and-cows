#include <iostream>
#include "host.h"
#include <set>
#include <algorithm>
#include <ncurses.h>

bool Host::is_number(std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int count_digit(int number) {
   int count = 0;
   while(number != 0) {
      number = number / 10;
      count++;
   }
   return count;
}


bool Host::initNumber(int length, int uBase) {
    set<int> bases({6,8,10});
    auto find = bases.find(uBase);
    if (find == bases.end()) {
        std::cout << "Only 6, 8 and 10 based systems available" << std::endl;
        return false;
    }

    if (length > uBase) {
        std::cout << "Length of number cannot be greater than base system" << std::endl;
        return false;
    }

    vector<char> number(length);

    srand(unsigned(time(NULL)));
    
    vector<bool> checks(uBase, false);
    for (int i = 0; i < length; i++) {
        short int d = (rand() % uBase);
        
        if (checks[d]) {
            i--;
            continue; // Skip duplicated digit
        }
        
        number[i] = '0' + d;
        checks[d] = true;
    }

    num = number;
    len = length;
    base = uBase;

    return true;
}

int Host::handleInput(string input) {
    if (input == "exit") {
        return 2;
    }
    if (input == "pass") {
        std::cout << "Game over... Secret number was: ";

        for (int i = 0; i < len; i++) {
            std::cout << num[i];
        }

        std::cout << std::endl;
        return -1;
    }
    if (!is_number(input)) {
        std::cout << "Only numbers allowed" << std::endl;
        return 0;
    }

    std::vector<char> digits(input.begin(), input.end());
    if (digits.size() != len) {
        std::cout << "Only " << len << "-digit numbers allowed" << std::endl;
        return 0;
    }

    return checkNumber(digits);
}

bool Host::checkNumber(vector<char>& digits) {
    int bulls = 0;
    int cows = 0;

    for (int i = 0; i < len; i++) {
        for (int j = 0; j < len; j++) {
            if (digits[i] == num[j]) {
                if (i == j) {
                    bulls++;
                    break;
                } else {
                    cows++;
                }
            }
        }
    }

    if (bulls == len) {
        return true;
    }

    std::cout << "Cows: " << cows << " , bulls: " << bulls << std::endl;

    return false;
}

/*int Host::newGame() {
    int ypos = 7;
    int xpos = 3;

    mvwprintw(solvewin, ypos, xpos, "Solve mode");
    wrefresh(solvewin);
    ypos++;


    int status = 3;

    while (status != 2) {

        if (status == 0) {
            char* input;
            wrefresh(solvewin);
            getstr(input);
            wrefresh(solvewin);
            //status = handleInput(input);
        } else if (status == 1) {
            mvwprintw(solvewin, ypos, xpos, "Congratulations! You won!");
            ypos++;
            status = 3;
        } else if (status == -1) {
            status = 3;
        } 
        else {
            mvwprintw(solvewin, ypos, xpos, "New game");
            ypos++;
            char* input;
            wrefresh(solvewin);
            getstr(input);
            wrefresh(solvewin);

            if (input == "exit") {
               endwin();
               return -1;
            }
            if (input == "mode") {
                endwin();
                return 2;
            }

            if (input == "help") {
              //  mvwprintw(menuwin, pivotY*(curr+1), pivotX, "Congratulations! You won!");
                continue;
            }
            string in = input;
            if (!is_number(in)) {
                mvwprintw(solvewin, ypos, xpos, "You can only ue numbers or helper commands");
                ypos++;
                continue;
            }


            mvwprintw(solvewin, ypos, xpos, "Enter base of numerical system");
            ypos++;

            char* uBase;
            refresh();
            getstr(uBase);
            refresh();

            bool flag = initNumber(stoi(input), stoi(uBase));
            if (flag) {
                mvwprintw(solvewin, ypos, xpos, "Secret number is ready. Enter your guess.");
                ypos++;
                status = 0;
            } else {
                status = 3;
            };
        }
    } 

    endwin();
    return 2;
}*/