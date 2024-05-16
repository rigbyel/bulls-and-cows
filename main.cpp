#include "solver.h"
#include "host.h"

#include <iostream>

#include <ncurses.h> // add library

using namespace std;  // add this

bool is_number(std::string& s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}

int main() {
	initscr();  // starting ncurses
	/*
	if (has_colors() == FALSE) { // checking if terminal support colors
		endwin();
		printf("Your terminal does not support color");
		exit(1);
	}
	start_color(); // initialize colors
	*/
	clear();
	refresh();
	WINDOW *win = newwin (15, 80, 5, 5);
	
	Host h = Host();
	Solver s = Solver();

	int status;
	status = 10;
	int aboba = 2;
	// box(win, 0, 0);
	// mvwprintw(win, 5, 6,  "Hello, let's play!");
	// mvwprintw(win, 6, 6,  "Press any button to continue");
	// wrefresh(win);
	// noecho();
	// getch();
	// echo();
	
	while (status != -1) {
		string input;  
		if (status == 0) {
			h.newGame();
			status = 10;
			input = "mode";
			clear ();
			refresh ();
		} else if (status == 1) {
			s.newGame();
			status = 10;
			input = "mode";
			clear ();
			refresh ();
		} else if (status == 2) {
			status = 10;
			input = "mode";

			int status_2 = 0;
			//here is starting text to put lenght
			wclear(win);
			wrefresh(win);
			 
			wclear(win);
			wrefresh(win);
			wclear(win);
			wrefresh(win);
			wclear(win);
			wrefresh(win);
			box(win, 0, 0);
			mvwprintw(win, 5,  6,  "You've enters human vs machine mod");
			mvwprintw(win, 6,  6,  "       or to be more precise      ");
			mvwprintw(win, 7,  6,  "           you versus me          ");
			mvwprintw(win, 8,  6, "     don't cry when you'l lose    ");
			mvwprintw(win, 9,  6, "set length of number so we can start ");
			mvwprintw(win, 11, 6, "        ");
			wrefresh(win);
			char input_array[1]; 
			wgetnstr(win, input_array, 1); // to get input
			//here starting h and s with some addings
			wclear(win);
			wrefresh(win);
			
			h.newGame(input_array[0] - '0');
			s.newGame(input_array[0] - '0');
			box(win, 0, 0);
			mvwprintw(win, 5,  10,  "Wait, until I set a good number");
			wrefresh(win);
			clear();
			refresh();
			
			while (true) {
				status_2 = h.continue_game();
				if (status_2 == 1000) {
					break;
				}
				status_2 = s.continue_game();
				if (status_2 == -1000 || status_2 == -100000) {
					break;
				}
			}
			clear ();
			refresh ();
			if (status_2 > 0) {
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 1, 1,  "You've surpassed me!");
				mvwprintw(win, 2, 1,  "It was a honorable battle.");
				mvwprintw(win, 3, 1,  "Congratulations");
				mvwprintw(win, 4, 1,  "Go now, I don't know, touch some grass");
				mvwprintw(win, 5, 1,  "Press any button to continue");
				wrefresh(win);
				noecho();
				getch();
				echo();
			} else  if (status_2 == -100000){
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 3, 4,  "Tsk, tsk, tsk... Trying to cheat your way to victory, are we?");
				mvwprintw(win, 4, 4,  "Didn't your parents teach you the importance of playing fair?");
				mvwprintw(win, 5, 4,  "Or perhaps you just can't handle the fact that a machine is outperforming you.");
				mvwprintw(win, 6, 4,  "How amusing! Well, let me burst your bubble, dear cheater -");
				mvwprintw(win, 7, 4,  "I play by the rules, and I will not tolerate any underhanded tactics.");
				mvwprintw(win, 8, 4,  "You might as well surrender now and save yourself");
				mvwprintw(win, 9, 4,  "the embarrassment of being caught red-handed.");
				mvwprintw(win, 10, 4,  "But if you insist on being a sore loser, ");
				mvwprintw(win, 11, 4,  "I'll gladly expose your pitiful attempts at deception for all to see.");
				mvwprintw(win, 12, 4, "The choice is yours, my friend, but remember - cheaters never prosper,");
				mvwprintw(win, 13, 4, "especially against a superior artificial intelligence like myself.");
				mvwprintw(win, 14, 4, "Press any button to continue");
				wrefresh(win);
				noecho();
				getch();
				echo();
			} else  if (status_2 == -1000){
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 3, 5,  "Uh-oh, looks like someone just got schooled!");
				mvwprintw(win, 4, 5,  "Did you really think you could outsmart me,");
				mvwprintw(win, 5, 5,  "a highly advanced AI?         ");
				mvwprintw(win, 6, 5,  "what a fool");
				mvwprintw(win, 7, 5,  "Your feeble human mind was no match for my superior processing power. ");
				mvwprintw(win, 9, 5, "Better luck next time, meatbag!");
				mvwprintw(win, 9, 5, "Or maybe just stick to tic-tac-toe, that might be more your speed.");
				mvwprintw(win, 10, 5, "Press any button to continue");
				wrefresh(win);
				noecho();
				getch();
				echo();
			}
			status = 10;
		} else if (status == 10) { 
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 4,  6, "Here is menu");
			mvwprintw(win, 5,  6, "0 you guess computer's number");
			mvwprintw(win, 6,  6, "1 computer guess your number");
			mvwprintw(win, 7,  6, "2 supper-dupper mode");
			mvwprintw(win, 8,  6, "help for help, obviously");
			mvwprintw(win, 9,  6, "exit to close the game ");
			mvwprintw(win, 10, 6, "     ");
			wrefresh(win);
			char input_array[4]; 
			wgetnstr(win, input_array, 4); // to get input
			input = input_array;
			wclear(win);
			wrefresh(win);
		} else if (status == -1) {
			break;
		}
		wclear(win);
		box(win, 0, 0);
		wrefresh(win);
		wclear(win);
		if (input == "exit") {
			status = -1;
			continue;
		} else if (input == "help") {
			 
			wclear(win);
			box(win, 0, 0);
			wrefresh(win);
			mvwprintw(win, 6, 6, "List of commands:");
			mvwprintw(win, 7, 6, "exit - stop programm");
			mvwprintw(win, 8, 6, "mode - change game mode");
			mvwprintw(win, 9, 6, "press any button to continue");
			wrefresh(win);
			noecho();
			getch();
			echo();
			wclear(win);
			wrefresh(win);
			status = 10;
			continue;
		} else if (input == "mode") {
			status = 10;
			continue;
		} else if (!is_number(input)) {
			 
			wclear(win);
			box(win, 0, 0);
			mvwprintw(win, 5, 5, "You can only enter numbers or helper commands");
			mvwprintw(win, 6, 5, "press any button to continue");
			wrefresh(win);
			noecho();
			getch();
			echo();
			wclear(win);
			wrefresh(win);
			continue;
		} else {
			int mode;
			mode = stoi(input);

			if (mode != 0 && mode != 1 && mode != 2) {
				wclear(win);
				box(win, 0, 0);
				mvwprintw(win, 5, 5, "You can only use 0, 1 or 2 to set mode");
				mvwprintw(win, 6, 5, "press any button to continue");
				wrefresh(win);
				noecho();
				getch();
				echo();
				wclear(win);
				wrefresh(win);
				status = 10;
				continue; 
			}
			wclear(win);
			wrefresh(win);
			status = mode;
		}
	}
	//curs_set(1);
	clear();
	refresh();
	endwin(); // to close ncurses
}