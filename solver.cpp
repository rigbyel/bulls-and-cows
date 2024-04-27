#include "solver.h"
#include <algorithm>

#include <iostream>


bool checkUnique(int num)
{
    bool visited[10] = {false};

    while (num)
    {
        if (visited[num % 10])
            break;

        visited[num%10] = true;

        num = num/10;
    }

    if (num == 0) {
        return true;
    }

    return false;
}

void  Solver::initNums(int length) {
    std::set<int> posNumsTemp;

    len = length;

    int minNum, maxNum;
    minNum = 1;
    for (int i = 0; i < len-1; i++) {
        minNum *= 10;
    }

    maxNum = minNum * 10;

    for (int i = minNum; i < maxNum; i++) {
        if (checkUnique(i)) {
            posNumsTemp.insert(i);
        }
    }

    posNums = posNumsTemp;
    
}

bool Solver::checkNum(int num, int ans, std::set<int>& filt) {
    int count = bulls + cows;
    int posCount = bulls;

    int i = 0;
    while (num)
    {
        if (const bool is_in = filt.find(num%10) != filt.end()) {
            count--;
        }

        if (num%10 == ans%10) {
            posCount--;
        }

        num = num/10;
        ans = ans/10;
    }

    return count == 0 && posCount == 0;
}

void Solver::delNums(int num) {
    int ans = num;

    std::set<int>filters;
    while (num) {
        filters.insert(num%10);
        num /= 10;
    }

    std::set<int>numsToDel;
    for (auto n : posNums) {
        if (!checkNum(n, ans, filters)) {
            numsToDel.insert(n);
        }
    }

    for (auto n : numsToDel) {
        posNums.erase(n);
    }
}

int Solver::guessNum() {
    if (posNums.empty()) {
    return -1;
    } 

    auto it = posNums.cbegin(); 
    return *it;
}

int Solver::handleInput() {

    int b, c;

    std::cout << "Enter cows: ";
    std::cin >> c;

    std::cout << "Enter bulls: ";
    std::cin >> b;

    if (b+c > len) {
        return -1;
    }
    if (b == len) {
        return 3;
    }

    bulls = b;
    cows = c;

    return 0;
}

int Solver::newGame() {
    int status = 1;
    int guess;

    while (status != -1) {
        if (status == 0)
        {
            guess = guessNum();
            tries++;

            if (guess == -1) {
                std::cout << "Lie detected\n"; 
                status = 1;
                continue;
            }
            std::cout << guess << std::endl;

            int st;
            st = handleInput();
            if (st != -1) {
                delNums(guess);
                if (st == 3) {
                    status = 3;
                    ans = guess;
                }
            } else {
                std::cout << "Lie detected\n"; 
                status = 1;
                continue;
            } 

            if (posNums.size() == 1) {
                status = 3;
                ans = guessNum();
                tries++;
            }

        } else if (status == 1) {
            std::cout << "New game. Enter your number length or enter 'help' for other commands\n";

            int length;
            std::string input;

            std::cin >> input;
            if (input == "help") {
                std::cout << "List of commands:\nexit - stop programm\nmode - change game mode\n" << std::endl;
                continue;
            }
            if (input == "exit") {
                return -1;
            }
            if (input == "mode") {
                return 2;
            }
            if (!is_number(input)) {
                std::cout << "You can only enter numbers or helper commands" << std::endl;
                continue;
            }
            
            length = stoi(input);
            initNums(length);

            status = 0;
            tries = 0;

        } else if (status == 3) {
            std::cout << "Your number is: " << ans << "\nNumber of tries: "<< tries << std::endl;
            status = 1;
        }
    }

    return 2;
}

bool Solver::is_number(std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}