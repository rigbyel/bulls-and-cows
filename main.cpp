#include "solver.h"
#include "host.h"
#include <string.h>

#include <iostream>

#include <ncurses.h> // add library

using namespace std;  // add this

void super_duper_mode (int psbl, WINDOW* win, Host h, Solver s) {
	// РљРѕРґ РґР»СЏ СЂРµР¶РёРјР° "Super-duper mode"
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
	
	
	if (input_array[0] == '0' || strlen(input_array) == 0) {
		wclear(win);
		box(win, 0, 0);
		mvwprintw(win, 5,  6,  "You've enter 0, so I changed it to 1");
		mvwprintw(win, 6,  6,  "I hope you'l be able to accept it");
		mvwprintw(win, 6,  6,  "Press any button to continue");
		input_array[0] = '1';
		wrefresh(win);
		noecho();
		getch();
		echo();
	}
	wclear(win);
	wrefresh(win);
	
	h.newGame(input_array[0] - '0');
	s.newGame(input_array[0] - '0', psbl);
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
		mvwprintw(win, 3, 4,  "You've surpassed me!");
		mvwprintw(win, 4, 4,  "It was a honorable battle.");
		mvwprintw(win, 5, 4,  "Congratulations");
		mvwprintw(win, 6, 4,  "Go now, I don't know, touch some grass");
		mvwprintw(win, 7, 4,  "Press any button to continue");
		wrefresh(win);
		noecho();
		getch();
		echo();
	} else  if (status_2 == -100000){
		wclear(win);
		box(win, 0, 0);
		mvwprintw(win, 3, 4,  "Tsk, tsk, tsk... Trying to cheat your way to victory, are we?");
		mvwprintw(win, 4, 4,  "Didn't your parents teach you the importance of playing fair?");
		mvwprintw(win, 5, 4,  "Or perhaps you just can't handle the fact");
		mvwprintw(win, 6, 4,  "that a machine is outperforming you.");
		mvwprintw(win, 7, 4,  "How amusing! Well, let me burst your bubble, dear cheater -");
		mvwprintw(win, 8, 4,  "I play by the rules, and I will not tolerate any underhanded tactics.");
		mvwprintw(win, 9, 4,  "You might as well surrender now and save yourself");
		mvwprintw(win, 10, 4,  "the embarrassment of being caught red-handed.");
		mvwprintw(win, 11, 4, "But if you insist on being a sore loser, ");
		mvwprintw(win, 12, 4, "I'll gladly expose your pitiful attempts at deception for all to see.");
		mvwprintw(win, 13, 4, "The choice is yours, my friend, but remember - cheaters never prosper,");
		mvwprintw(win, 14, 4, "especially against a superior artificial intelligence like myself.");
		mvwprintw(win, 15, 4, "Press any button to continue");
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
}

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
	keypad(stdscr, TRUE); // Р’РєР»СЋС‡РµРЅРёРµ СЃРїРµС†РёР°Р»СЊРЅС‹С… РєР»Р°РІРёС€ (СЃС‚СЂРµР»РѕС‡РєРё Рё РґСЂ.)
	clear();
	refresh();
	WINDOW *win = newwin (18, 80, 5, 5);
	
	Host h = Host();
	Solver s = Solver();

	box(win, 0, 0);
	mvwprintw(win, 5, 6,  "Hello, let's play!");
	mvwprintw(win, 6, 6,  "Press any button to continue");
	wrefresh(win);
	noecho();
	getch();
	echo();
	int status_2 = 0;
	int currentSelection = 0; // РўРµРєСѓС‰РёР№ РІС‹Р±СЂР°РЅРЅС‹Р№ РїСѓРЅРєС‚
    int numOptions = 5; // РљРѕР»РёС‡РµСЃС‚РІРѕ РїСѓРЅРєС‚РѕРІ РІ РјРµРЅСЋ
	
	
	while (true) {
		werase(win); // РћС‡РёСЃС‚РєР° СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР°
		box(win, 0, 0); // Р РёСЃРѕРІР°РЅРёРµ СЂР°РјРєРё РІРѕРєСЂСѓРі РѕРєРЅР°

		// РћС‚РѕР±СЂР°Р¶РµРЅРёРµ РїСѓРЅРєС‚РѕРІ РјРµРЅСЋ РІ РѕРєРЅРµ win
		for (int i = 0; i < numOptions; i++) {
			if (i == currentSelection) {
				wattron(win, A_REVERSE); // РџРѕРґСЃРІРµС‚РєР° РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р°
			}
			switch (i) {
				case 0:
					mvwprintw(win, i + 1, 2, "1 You guess computer's number"); // С‚СѓС‚ СЂРµР¶РёРј РїСЂРѕС‚РёРІ РєРѕРјРїР°
					break;
				case 1:
					mvwprintw(win, i + 1, 2, "2 Computer guess your number"); // С‚СѓС‚ РєРѕРјРї СѓРіР°РґС‹РІР°РµС‚ С‚РІРѕС‘ С‡РёСЃР»Рѕ
					break;
				case 2:
					mvwprintw(win, i + 1, 2, "3 Super-duper mode");
					break;
				case 3:
					mvwprintw(win, i + 1, 2, "4 Show help");
					break;
				case 4:
					mvwprintw(win, i + 1, 2, "5 Exit");
					break;
			}
			if (i == currentSelection) {
				wattroff(win, A_REVERSE); // РЎРЅСЏС‚РёРµ РїРѕРґСЃРІРµС‚РєРё
			}
		}

		wrefresh(win); // РћР±РЅРѕРІР»РµРЅРёРµ СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР° РЅР° СЌРєСЂР°РЅРµ

		int key = getch(); // РџРѕР»СѓС‡РµРЅРёРµ РЅР°Р¶Р°С‚РѕР№ РєР»Р°РІРёС€Рё

		switch (key) {
			case KEY_UP:
				currentSelection = (currentSelection - 1 + numOptions) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРІРµСЂС…
				break;
			case KEY_DOWN:
				currentSelection = (currentSelection + 1) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРЅРёР·
				break;
			case '\n': // Р’С‹Р±РѕСЂ РїСѓРЅРєС‚Р° РїРѕ РЅР°Р¶Р°С‚РёСЋ Enter
				// Р—РґРµСЃСЊ РјРѕР¶РЅРѕ РґРѕР±Р°РІРёС‚СЊ РєРѕРґ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р° РјРµРЅСЋ
				int currentSelection2 = 0;
				int numOptions2 = 5;
				bool if_exit = false;
				switch (currentSelection) {
					case 0:
						// РљРѕРґ РґР»СЏ СЂРµР¶РёРјР° "You guess computer's number"
						h.newGame();
						clear ();
						refresh ();
						break;
					case 1:
						// РљРѕРґ РґР»СЏ СЂРµР¶РёРјР° "Computer guess your number"
						
						while (true) {
							werase(win); // РћС‡РёСЃС‚РєР° СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР°
							box(win, 0, 0); // Р РёСЃРѕРІР°РЅРёРµ СЂР°РјРєРё РІРѕРєСЂСѓРі РѕРєРЅР°

							// РћС‚РѕР±СЂР°Р¶РµРЅРёРµ РїСѓРЅРєС‚РѕРІ РјРµРЅСЋ РІ РѕРєРЅРµ win
							for (int j = 0; j < numOptions2; j++) {
								if (j == currentSelection2) {
									wattron(win, A_REVERSE); // РџРѕРґСЃРІРµС‚РєР° РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р°
								}
								switch (j) {
									case 0:
										mvwprintw(win, j + 1, 2, "1 Easy"); // С‚СѓС‚ СЂРµР¶РёРј РїСЂРѕС‚РёРІ РєРѕРјРїР°
										break;
									case 1:
										mvwprintw(win, j + 1, 2, "2 Medium"); // С‚СѓС‚ РєРѕРјРї СѓРіР°РґС‹РІР°РµС‚ С‚РІРѕС‘ С‡РёСЃР»Рѕ
										break;
									case 2:
										mvwprintw(win, j + 1, 2, "3 Hard");
										break;
									case 3:
										mvwprintw(win, j + 1, 2, "4 Imposible");
										break;
									case 4:
										mvwprintw(win, j + 1, 2, "5 Exit");
										break;
								}
								if (j == currentSelection2) {
									wattroff(win, A_REVERSE); // РЎРЅСЏС‚РёРµ РїРѕРґСЃРІРµС‚РєРё
								}
							}

							wrefresh(win); // РћР±РЅРѕРІР»РµРЅРёРµ СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР° РЅР° СЌРєСЂР°РЅРµ

							int key2 = getch(); // РџРѕР»СѓС‡РµРЅРёРµ РЅР°Р¶Р°С‚РѕР№ РєР»Р°РІРёС€Рё

							switch (key2) {
								case KEY_UP:
									currentSelection2 = (currentSelection2 - 1 + numOptions) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРІРµСЂС…
									break;
								case KEY_DOWN:
									currentSelection2 = (currentSelection2 + 1) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРЅРёР·
									break;
								case '\n': // Р’С‹Р±РѕСЂ РїСѓРЅРєС‚Р° РїРѕ РЅР°Р¶Р°С‚РёСЋ Enter
									// Р—РґРµСЃСЊ РјРѕР¶РЅРѕ РґРѕР±Р°РІРёС‚СЊ РєРѕРґ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р° РјРµРЅСЋ
									switch (currentSelection2) {
										case 0:
											s.newGame(25);
											break;
										case 1:
											s.newGame(50);
											break;
										case 2:
											s.newGame(75);
											break;
										case 3:
											s.newGame(99);
											break;
										case 4:
											if_exit = true;
											break;
									}
							}
							if (if_exit) {
								break;
							}
						}
						clear ();
						refresh ();
						break;
					case 2:
						while (true) {
							werase(win); // РћС‡РёСЃС‚РєР° СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР°
							box(win, 0, 0); // Р РёСЃРѕРІР°РЅРёРµ СЂР°РјРєРё РІРѕРєСЂСѓРі РѕРєРЅР°

							// РћС‚РѕР±СЂР°Р¶РµРЅРёРµ РїСѓРЅРєС‚РѕРІ РјРµРЅСЋ РІ РѕРєРЅРµ win
							for (int j = 0; j < numOptions2; j++) {
								if (j == currentSelection2) {
									wattron(win, A_REVERSE); // РџРѕРґСЃРІРµС‚РєР° РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р°
								}
								switch (j) {
									case 0:
										mvwprintw(win, j + 1, 2, "1 Easy"); // С‚СѓС‚ СЂРµР¶РёРј РїСЂРѕС‚РёРІ РєРѕРјРїР°
										break;
									case 1:
										mvwprintw(win, j + 1, 2, "2 Medium"); // С‚СѓС‚ РєРѕРјРї СѓРіР°РґС‹РІР°РµС‚ С‚РІРѕС‘ С‡РёСЃР»Рѕ
										break;
									case 2:
										mvwprintw(win, j + 1, 2, "3 Hard");
										break;
									case 3:
										mvwprintw(win, j + 1, 2, "4 Imposible");
										break;
									case 4:
										mvwprintw(win, j + 1, 2, "5 Exit");
										break;
								}
								if (j == currentSelection2) {
									wattroff(win, A_REVERSE); // РЎРЅСЏС‚РёРµ РїРѕРґСЃРІРµС‚РєРё
								}
							}

							wrefresh(win); // РћР±РЅРѕРІР»РµРЅРёРµ СЃРѕРґРµСЂР¶РёРјРѕРіРѕ РѕРєРЅР° РЅР° СЌРєСЂР°РЅРµ

							int key2 = getch(); // РџРѕР»СѓС‡РµРЅРёРµ РЅР°Р¶Р°С‚РѕР№ РєР»Р°РІРёС€Рё

							switch (key2) {
								case KEY_UP:
									currentSelection2 = (currentSelection2 - 1 + numOptions) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРІРµСЂС…
									break;
								case KEY_DOWN:
									currentSelection2 = (currentSelection2 + 1) % numOptions; // РџРµСЂРµРјРµС‰РµРЅРёРµ РІРЅРёР·
									break;
								case '\n': // Р’С‹Р±РѕСЂ РїСѓРЅРєС‚Р° РїРѕ РЅР°Р¶Р°С‚РёСЋ Enter
									// Р—РґРµСЃСЊ РјРѕР¶РЅРѕ РґРѕР±Р°РІРёС‚СЊ РєРѕРґ РґР»СЏ РѕР±СЂР°Р±РѕС‚РєРё РІС‹Р±СЂР°РЅРЅРѕРіРѕ РїСѓРЅРєС‚Р° РјРµРЅСЋ
									switch (currentSelection2) {
										case 0:
											super_duper_mode(25, win, h, s);
											break;
										case 1:
											super_duper_mode(50, win, h, s);
											break;
										case 2:
											super_duper_mode(75, win, h, s);
											break;
										case 3:
											super_duper_mode(99, win, h, s);
											break;
										case 4:
											if_exit = true;
											break;
									}
							}
							if (if_exit) {
								break;
							}
						}
						clear ();
						refresh ();
						break;
						break;
					case 3:
						// РљРѕРґ РґР»СЏ РїРѕРєР°Р·Р° РїРѕРјРѕС‰Рё
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
						break;
					case 4:
						delwin(win); // РЈРґР°Р»РµРЅРёРµ РѕРєРЅР° win
						endwin(); // Р—Р°РІРµСЂС€РµРЅРёРµ ncurses
						return 0; // Р’С‹С…РѕРґ РёР· РїСЂРѕРіСЂР°РјРјС‹
				}
				break;
		}
	}
	//curs_set(1);
	clear();
	refresh();
	endwin(); // to close ncurses
}