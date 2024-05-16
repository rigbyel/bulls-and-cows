#include <iostream>
#include "host.h"
#include <set>
#include <algorithm>

bool Host::is_number(std::string& s) {
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

bool Host::initNumber(int length, int uBase, WINDOW *win) {
    set<int> bases({6,8,10});
    auto find = bases.find(uBase);
    if (find == bases.end()) {
        //std::cout << "Only 6, 8 and 10 based systems available" << std::endl;
		
		box(win, 0, 0);
		wclear(win);
		// mvprintw(5, 8, "Only 6, 8 and 10 based systems available");
		// mvprintw(6, 8, "Press any button to continue");
		mvwprintw(win, 1, 1, "Only 6, 8 and 10 based systems available");
		mvwprintw(win, 2, 1, "Press any button to continue");
		wrefresh(win);
		getch();
        return false;
    }

    if (length > uBase) {
        //std::cout << "Length of number cannot be greater than base system" << std::endl;
		box(win, 0, 0);
		wclear(win);
		// mvprintw(5, 8, "Length of number cannot be greater than base system");
		// mvprintw(6, 8, "Press any button to continue");
		mvwprintw(win, 1, 1, "Length of number cannot be greater than base system");
		mvwprintw(win, 2, 1, "Press any button to continue");
		wrefresh(win);
		getch();
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

bool Host::initNumber(int length) {
    
	vector<char> number(length);

    srand(unsigned(time(NULL)));
    
    vector<bool> checks(10, false);
    for (int i = 0; i < length; i++) {
        short int d = (rand() % 10);
        
        if (checks[d]) {
            i--;
            continue; // Skip duplicated digit
        }
        
        number[i] = '0' + d;
        checks[d] = true;
    }
    num = number;
    len = length;
    base = 10;
    return true;
}

int Host::handleInput(string input, WINDOW *win, WINDOW *win_cow) {
    if (input == "exit") {
        return 2;
    }
    if (input == "pass") {
        /*std::cout << "Game over... Secret number was: ";
	
        for (int i = 0; i < len; i++) {
            std::cout << num[i];
        }

        std::cout << std::endl;
		*/
		
		box(win, 0, 0);
		wclear(win);
		
		// mvprintw(5, 8, "Game over... Secret number was: ");
		
		char num_array [num.size()];
		for (int i =0; i < num.size(); i++) {
			num_array[i] = num[i];
		}
		// mvprintw(6, 8, num_array);
		// mvprintw(7, 8, "Press any button to continue");
		mvwprintw(win, 1, 1, "Game over... Secret number was:");
		mvwprintw(win, 2, 1, num_array);
		mvwprintw(win, 3, 1, "Press any button to continue");
		wrefresh(win);
		getch();
		
        return -1;
    } else if (input == "mode") {
		return 2;
	}
    if (!is_number(input)) { // may not be ised at all
        //std::cout << "Only numbers allowed" << std::endl;
		wclear(win);
		box(win, 0, 0);
		// mvprintw(5, 8, "Only numbers allowed");
		// mvprintw(6, 8, "Press any button to continue");
		mvwprintw(win, 1, 1, "Only numbers allowed");
		mvwprintw(win, 2, 1, "Press any button to continue");
		wrefresh(win);
		wrefresh(win);
		getch();
        return 1488;
    }

    std::vector<char> digits(input.begin(), input.end());
    if (digits.size() != len) {
        //std::cout << "Only " << len << "-digit numbers allowed" << std::endl;
		wclear(win);
		box(win, 0, 0);
		string out_put = "Only ";
		out_put += to_string(len);
		out_put += "-digit numbers allowed";
		const char* out_put_array = out_put.c_str();
		// mvprintw(5, 8, out_put_array);
		// mvprintw(6, 8, "Press any button to continue");
		mvwprintw(win, 1, 1, out_put_array);
		mvwprintw(win, 2, 1, "Press any button to continue");
		wrefresh(win);
		getch();
		return 1488;
    }

    return checkNumber(digits, win_cow);
}

bool Host::checkNumber(vector<char>& digits, WINDOW *win) {
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

    //std::cout << "Cows: " << cows << " , bulls: " << bulls << std::endl;
	//mvprintw(5, 8, "Cows: ", cows+"0", " , bulls: ", bulls + "0");
	string out_put = "Cows: ";
	out_put += to_string(cows);
	string out_put2 = "Bulls: ";
	out_put2 += to_string(bulls);
	const char* out_put_array = out_put.c_str();
	// mvprintw(5, 8, out_put_array);
	// mvprintw(6, 8, "Press any button to continue");
	wclear(win);
	box(win, 0, 0);
	mvwprintw(win, 1, 1, out_put_array);
	mvwprintw(win, 3, 1, out_put2.c_str());
	//mvwprintw(win, 1, 0, "Press any button to continue");
	wrefresh(win);
	//getch();
    return false;
}

int Host::newGame() {
	// echo();
	clear();
	refresh();
	WINDOW *win_cow = newwin(5, 70, 1, 7);
	WINDOW *win = newwin(10, 100, 8, 8);
    //std::cout << "Welcome to bulls and cows game!" << std::endl;
	
	// mvprintw(5, 8, "Welcome to bulls and cows game!");
	mvwprintw(win, 1, 1, "Welcome to bulls and cows game!");
	mvwprintw(win, 2, 1, "Press any button to continue");
	wrefresh(win);

    int status = 3;

    while (status != 2) {

        if (status == 0 || status == 1488) {
            string input;
            //std::cin >> input; 
			char input_array[10];
			// char input_array[uBase];
			wclear(win);
			box(win, 0, 0);
			//mvprintw(5, 8, "Your number is ");
			mvwprintw(win, 1, 1, "Your number is ");
			wrefresh(win);
			wgetnstr(win, input_array, 10); // to get input
			input = input_array;
            status = handleInput(input, win, win_cow);
        } else if (status == 1) {
            //std::cout << "Congratulations, you win!" << std::endl;
			
			wclear(win);
			box(win, 0, 0);
			// mvprintw(5, 8, "Congratulations, you win!");
			// mvprintw(9, 8, "Press any button to continue");			
			mvwprintw(win, 1, 1, "Congratulations, you win!");
			mvwprintw(win, 2, 1, "Press any button to continue");
			wrefresh(win);
			box(win, 0, 0);
			//wclear(win_cow);
			//wrefresh(win_cow);
			getch();
            status = 3;
			return 0;
        } else if (status == -1) {
            status = 3;
        } 
        else {
            //std::cout << "Enter new number length to start a new game or enter 'help' for more commands" << std::endl;
        
			wclear(win);
			box(win, 0, 0);
			// mvprintw(5, 8, "Enter new number length to start a new game or enter 'help' for more commands");
			// mvprintw(6, 9, "");
			mvwprintw(win, 1, 1, "Enter length of number length to start a new game or enter 'help' for more commands");
			mvwprintw(win, 2, 1, "   ");
			
			wrefresh(win);
			
			int uBase;
            string input;
            //std::cin >> input; 
			
			
			char input_array[10]; 
			wgetnstr(win, input_array, 10); // to get input
			input = input_array;



            if (input == "exit") {
               return -1;
            }
            if (input == "mode") {
                return 2;
            }

            if (input == "help") {
                //std::cout << "List of commands:\nexit - stop programm\nmode - change game mode\n" << std::endl;
				wclear(win);
				box(win, 0, 0);
				// mvprintw(5, 8, "List of commands:");
				// mvprintw(6, 8, "exit - stop programm");
				// mvprintw(7, 8, "mode - change game mode");
				// mvprintw(8, 8, "press any button to continue");				
				mvwprintw(win, 1, 1, "List of commands:");
				mvwprintw(win, 2, 1, "exit - stop programm");
				mvwprintw(win, 3, 1, "mode - change game mode");
				mvwprintw(win, 4, 1, "press any button to continue");

				wrefresh(win);
				getch();
				continue;
            }
            if (!is_number(input)) {
                //std::cout << "You can only enter numbers or helper commands" << std::endl;
				wclear(win);
				box(win, 0, 0);
				// mvprintw(5, 8, "You can only enter numbers or helper commands");
				// mvprintw(6, 8, "press any button to continue");						
				mvwprintw(win, 1, 1, "You can only enter numbers or helper commands");
				mvwprintw(win, 2, 1, "press any button to continue");
				
				wrefresh(win);
				getch();
				continue;
            }


            //std::cout << "Enter base of numerical system you want play in: " << std::endl;
			wclear(win);
			box(win, 0, 0);
			// mvprintw(5, 8, "Enter base of numerical system you want play in: ");					
			mvwprintw(win, 1, 1, "Enter base of numerical system you want play in: ");
			wrefresh(win);
			
			//std::cin >> uBase; 

			char uBase_array[2];
			wgetnstr(win, uBase_array, 2);
			uBase = atoi (uBase_array);

            bool flag = initNumber(stoi(input), uBase, win);
            if (flag) {
                //std::cout << "Secret number is ready!\nEnter your guess or enter 'pass' to give up" << std::endl;
                //wclear(win);
				// mvprintw(5, 8, "Secret number is ready!");				
				// mvprintw(6, 8, "Enter your guess or enter 'pass' to give up");				
				// mvprintw(7, 8, "Press any button to continue");
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1, "Secret number is ready!");
				mvwprintw(win, 2, 1, "Enter your guess or enter 'pass' to give up");
				mvwprintw(win, 3, 1, "Press any button to continue");
				wrefresh(win);
				getch();
				//getch();
				status = 0;
            } else {
                status = 3;
            };
        }
    } 
	// noecho();

    return 10;
}

int Host::newGame(int zeleboba) {
	num.clear();
    int status = 3;
	int uBase = 10;
	bool flag = initNumber(zeleboba);
	global_status = 0;
    return 10;
}

int Host::continue_game () {
	WINDOW *win_cow = newwin(5, 70, 1, 8);
	WINDOW *win = newwin(10, 70, 8, 8);
	
	box(win, 0, 0);
	box(win_cow, 0, 0);
	
	wrefresh(win);
	wrefresh(win_cow);
	
    while (global_status != 2) {
        if (global_status != 1 || global_status != -1) {
            string input;
            //std::cin >> input; 
			char input_array[10];
			wclear(win);
			box(win, 0, 0);
			//mvprintw(5, 8, "Your number is ");
			mvwprintw(win, 2, 2, "Your number is ");
			wrefresh(win);
			wgetnstr(win, input_array, 10); // to get input
			input = input_array;
            global_status = handleInput(input, win, win_cow);
			if (global_status == 1488) {
				continue;
			} else {
				return 10;
				
			}
        } else if (global_status == 1) {
            return 1000;
        } else if (global_status == -1) {
            global_status = 3;
        } 
    }

    return 10;
}