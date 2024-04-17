#include <iostream>
#include "host.h"
#include <set>
#include <algorithm>

bool is_number(std::string& s)
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
                    cows++;
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

void Host::newGame() {
    std::cout << "Welcome to bulls and cows game!" << std::endl;

    int status = 3;

    while (status != 2) {

        if (status == 0) {
            string input;
            std::cin >> input; 
            status = handleInput(input);
        } else if (status == 1) {
            std::cout << "Congratulations, you win!" << std::endl;
            status = 3;
        } else if (status == -1) {
            status = 3;
        } 
        else {
            std::cout << "Enter new number length to start a new game or enter 'exit' to stop programm." << std::endl;
            int uBase;
            string input;
            std::cin >> input; 

            if (input == "exit") {
               status = 2;
               continue;
            }
            if (!is_number(input)) {
                std::cout << "You can only enter numbers or helper commands" << std::endl;
                continue;
            }


            std::cout << "Enter base of numerical system you want play in: " << std::endl;
            std::cin >> uBase; 

            bool flag = initNumber(stoi(input), uBase);
            if (flag) {
                std::cout << "Secret number is ready!\nEnter your guess or enter 'pass' to give up" << std::endl;
                status = 0;
            } else {
                status = 3;
            };
        }
    } 
}