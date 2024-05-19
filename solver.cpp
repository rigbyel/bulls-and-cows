#include "solver.h"
#include <algorithm>
#include <cstdlib> 
#include <cmath>

#include <iostream>


bool checkUnique(int num) {
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

/*
int Solver::guessNum() {
    if (posNums.empty()) {
    return -1;
    } 

    auto it = posNums.cbegin(); 
    return *it;
}
*/

int Solver::guessNum() {
    if (posNums.empty()) {
    return -1;
    } 

    static bool first = true;
    if (first) 
    {  
      srand( time(NULL) ); //seeding for the first time only!
      first = false;
    }
    int mode = rand() % 100;

    if (mode < psbl) {
        auto it = posNums.cbegin(); 
        return *it;
    }

    int max = int(pow(10, len+1)) - 1;
    int min = int(pow(10, len));

    return (min + rand() % (( max + 1 ) - min)) / 10;
}

int Solver::handleInput(WINDOW *win) {
	wclear (win);
	box(win, 0, 0);
    int b, c;

    // std::cout << "Enter cows: ";
    // std::cin >> c;
	mvwprintw(win, 1, 1, "Enter cows: ");
	wrefresh(win);
	char cow_array[4];
	wgetnstr(win, cow_array, 4);
	c = cow_array[0] - '0';
    // std::cout << "Enter bulls: ";
    // std::cin >> b;
	mvwprintw(win, 2, 1, "Enter bulls: ");
	wrefresh(win);
	char bull_array[4];
	wgetnstr(win, bull_array, 4);
	b = bull_array[0] - '0';
	if (bull_array == "mode" || cow_array == "mode") {
		return 100;
	}
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

int Solver::newGame(int psbl_) {
	// echo();
	psbl = psbl_;
	clear();
	refresh();
	WINDOW *win_comp = newwin(5, 100, 2, 8);
	WINDOW *win = newwin(10, 100, 8, 8);
    int status = 1;
    int guess;

    while (status != -1) {
        if (status == 0)
        {
            guess = guessNum();
            tries++;

            if (guess == -1) {
                //std::cout << "Lie detected\n"; 
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "Lie detected");
				mvwprintw(win, 2, 1, "Press any button to continue");
				wrefresh(win);
				getch();
                status = 1;
                continue;
            }
            //std::cout << guess << std::endl;
			string nado = "I guess your number is ... " + to_string(guess);
			const char* guess_array = nado.c_str();
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 2, 2, guess_array);
			wrefresh(win);
			// mvwprintw(win, 0, 0, "Press any button to continue");

            int st;
            st = handleInput(win_comp);
            if (st != -1) {
                delNums(guess);
                if (st == 3) {
                    status = 3;
                    ans = guess;
                }
            } else if (st == 100){
				status = -1;
			} else {
                // std::cout << "Lie detected\n";
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "Lie detected");
				mvwprintw(win, 2, 1, "Press any button to continue");
				wrefresh(win);
				getch();
                status = 1;
                continue;
            } 

            if (posNums.size() == 1) {
                status = 3;
                ans = guessNum();
                tries++;
            }

        } else if (status == 1) {
            // std::cout << "New game. Enter your number length or enter 'help' for other commands\n";
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 1, 1, "New game. Enter your number length or enter 'help' for other commands");
			mvwprintw(win, 2, 1, "  ");
			wrefresh(win);
            int length;
            std::string input;

            // std::cin >> input;
			wrefresh(win);
			char input_array[4];
			wgetnstr(win, input_array, 4);
			input = input_array;
            if (input == "help") {
                // std::cout << "List of commands:\nexit - stop programm\nmode - change game mode\n" << std::endl;
                wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "List of commands:");
				mvwprintw(win, 2, 1, "exit - stop programm");
				mvwprintw(win, 3, 1, "mode - change game mode");
				mvwprintw(win, 4, 1, "Press any button to continue");
				wrefresh(win);
				getch();
				continue;
            }
            if (input == "exit") {
                return -1;
            }
            if (input == "mode") {
                return 2;
            }
            if (!is_number(input)) {
                // std::cout << "You can only enter numbers or helper commands" << std::endl;
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "You can only enter numbers or helper commands");
				mvwprintw(win, 2, 1, "Press any button to continue");
				wrefresh(win);
				getch();
                continue;
            }
            
            length = stoi(input);
            initNums(length);

            status = 0;
            tries = 0;

        } else if (status == 3) {
            //std::cout << "Your number is: " << ans << "\nNumber of tries: "<< tries << std::endl;
			string output = "Your number is: ";
			output += to_string(ans);
			string output2 = "Number of tries: ";
			output2 += to_string(tries);
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 1, 1, output.c_str());
			mvwprintw(win, 2, 1, output2.c_str());
			mvwprintw(win, 3, 1, "Press any button to continue");
			wclear(win_comp);
			box(win_comp, 0, 0);
			wrefresh(win_comp);
			wrefresh(win);
			getch();
            status = 1;
			return 0;
        }
    }
	// noecho();

    return 10;
}

int Solver::newGame(int zeleboba, int psbl_) {
	psbl = psbl_;
    int status = 1;
    int guess;       
	std::string input;
	input = to_string(zeleboba);
	len = stoi(input);
	initNums(len);
	status = 0;
	tries = 0;
	global_status = 0;
	schet = 0;
	WINDOW *win_comp = newwin(5, 50, 1, 80);
	WINDOW *win = newwin(10, 50, 8, 80);
	
	box(win, 0, 0);
	box(win_comp, 0, 0);
	
	wrefresh(win);
	wrefresh(win_comp);
    return 10;
}

bool Solver::is_number(std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

int Solver::continue_game () {
	WINDOW *win_comp = newwin(5, 50, 1, 80);
	WINDOW *win = newwin(10, 50, 8, 80);
	
	box(win, 0, 0);
	box(win_comp, 0, 0);
	
	wrefresh(win);
	wrefresh(win_comp);
	
    int guess = 1;

    while (global_status != -1) {
        if (schet == 5) {
			return - 100000;
		}
		
		if (global_status == 0) {
            guess = guessNum();
            tries++;

            if (guess == -1) {
                //std::cout << "Lie detected\n"; 
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "Lie detected");
				mvwprintw(win, 2, 1, "Press any button to continue");
				wrefresh(win);
				getch();
                global_status = 0;
				guess = 1;
				schet += 1;
                continue;
            }
            //std::cout << guess << std::endl;
			string nado = "I guess your number is ... " + to_string(guess);
			const char* guess_array = nado.c_str();
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 2, 2, guess_array);
			wrefresh(win);
			// mvwprintw(win, 0, 0, "Press any button to continue");

            int st;
            st = handleInput(win_comp);
            if (st != -1) {
                delNums(guess);
                if (st == 3) {
                    global_status = 3;
                    ans = guess;
                } else if (st == 0) {
					return 10;
				}
            } else {
                // std::cout << "Lie detected\n";
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "Lie detected");
				mvwprintw(win, 2, 1, "Press any button to continue");
				wrefresh(win);
				getch();
                global_status = 0;
				guess = 1;
				schet += 1;
                continue;
            } 

            if (posNums.size() == 1) {
                global_status = 3;
                ans = guessNum();
                tries++;
            }
        } else if (global_status == 3) {
            return -1000;
        }
    }

    return 10;
}