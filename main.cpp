#include "solver.h"
#include "host.h"

#include <iostream>


bool is_number(std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int main() {
    Host h = Host();
    Solver s = Solver();

    int status;
    status = 2;

    while (status != -1) {
        if (status == 0) {
            status = h.newGame();
        }
        if (status == 1) {
            status = s.newGame();
        }
        if (status == 2) {
            std::cout << "Enter 0 if you want to guess number or 1 if you want computer to guess it\nYou can also enter 'help' to know more commands" << std::endl;
        }

        if (status == -1) {
            break;
        }
        
        string input;
        std::cin >> input; 

        if (input == "exit") {
            status = -1;
            continue;
        }
        if (input == "help") {
            status = 2;
            std::cout << "List of commands:\nexit - stop programm\nmode - change game mode\n" << std::endl;
            continue;
        }
        if (input == "mode") {
            status = 2;
            continue;
        }
        
        if (!is_number(input)) {
            std::cout << "You can only enter numbers or helper commands" << std::endl;
            continue;
        }

        int mode;
        mode = stoi(input);

        if (mode != 0 && mode != 1) {
            std::cout << "You can only use 0 and 1 to set mode\n";
            status = 2;
            continue; 
        }

        status = mode;
    }
}