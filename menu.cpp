#include "menu.h"
#include <ncurses.h>

menu::menu(int height, int width) {
        getmaxyx(stdscr, y_max, x_max);
        _height = height;
        _width = width;
        menuwin = newwin(height, width, (y_max - height) / 2, (x_max - width) / 2);
        h = Host();

        //box(menuwin, 0, 0);
        wborder(menuwin, '|', '|', '-', '-', '+', '+', '+', '+');
        keypad(menuwin, true);
}

void menu::clean(){
        for (int i = 1; i < _height-1; i++) {
                for (int j = 1; j < _width - 1; j++) {
                        mvwprintw(menuwin, i, j, " ");
                }
        }
        wborder(menuwin, '|', '|', '-', '-', '+', '+', '+', '+');
}

int menu::start() {
    int choice;
    int difficulty;

    while (true)
    {
        choice = main_menu();
        clean();
        switch (choice)
        {
        case 0:
            break;
        case 1:
            solveGame();
            clean();
            break;
        case 2:
            difficulty = levels();
            clean();
            break;
        case 3:
            break;
        case 4:
            return 0;
        default:
            break;
        }
    }
    

    return 0;
}

int menu::main_menu() {
    
    int choice;
    int highlight = 0;

    while (true)
    {
        for (int i = 0; i < choices.size(); i++)
        {
            if (i == highlight)
            {
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, _height / 2 - 5 + 2*i +1, (_width - choices[i].size()) / 2, choices[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        wrefresh(menuwin);
        choice = wgetch(menuwin);
        
        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = choices.size()-1;
            }
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == choices.size())
            {
                highlight = 0;
            }
            break;
        case ' ':
            return highlight;
        default:
            break;        
        }
        
    }
}

void menu::stop() {
    endwin();
}

int menu::levels() {

    int choice;
    int highlight = 0;

    while (true)
    {
        for (int i = 0; i < levs.size(); i++)
        {
            if (i == highlight)
            {
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, _height / 2 - 5 + 2*i +1, (_width - levs[i].size()) / 2, levs[i].c_str());
            wattroff(menuwin, A_REVERSE);
        }

        wrefresh(menuwin);
        choice = wgetch(menuwin);
        
        switch (choice)
        {
        case KEY_UP:
            highlight--;
            if (highlight == -1)
            {
                highlight = levs.size()-1;
            }
            break;
        case KEY_DOWN:
            highlight++;
            if (highlight == levs.size())
            {
                highlight = 0;
            }
            break;
        default:
            break;        
        }

        if (choice == ' ')
        {   
            return highlight;
        }
        
    }

}

int menu::solveGame() {
    int ypos = 1;
    int xpos = 9;

    mvwprintw(menuwin, ypos, xpos, "Solve mode");
    ypos++;
    wrefresh(menuwin);

    int status = 0;
    int inpStat = 0;
    bool flag;
    string input;
    string baseInp;

    while (true)
    {
        switch (status)
        {
        case 0:
            mvwprintw(menuwin, ypos, xpos, "Length: ");
            ypos++;

            input = getstring(&ypos, &xpos);
            inpStat = handleInput(input);

            switch (inpStat)
            {
            case 0:
                mvwprintw(menuwin, ypos, xpos, "Base: ");
                ypos++;
            
                baseInp = getstring(&ypos, &xpos);
                mvwprintw(menuwin, ypos, xpos, "done");
                
                flag = h.initNumber(stoi(input), stoi(baseInp));

                if (flag) {
                    ypos = 1;
                    mvwprintw(menuwin, ypos, xpos, "Make a guess");
                    ypos++;

                    status = 1;
                } else {
                    mvwprintw(menuwin, ypos, xpos, "Unlucky");
                    status = 0;
                }

                break;
            case 3:
                mvwprintw(menuwin, ypos, xpos, "Not allowed");
                ypos++;
                status = 0;
                break;
            }

            break;
        
        default:
            break;
        }
    }
    
    

    int ch = wgetch(menuwin);
    return 0;
}

string menu::getstring(int* ypos, int* xpos)
{
    string input;

    // let the terminal do the line editing
    nocbreak();
    echo();

    mvwprintw(menuwin, *ypos, *xpos-1, " ");
    wrefresh(menuwin);

    // this reads from buffer after <ENTER>, not "raw" 
    // so any backspacing etc. has already been taken care of
    int ch = wgetch(menuwin);

    while ( ch != 10 )
    {
        input.push_back( ch );
        ch = wgetch(menuwin);
    }

    cbreak();
    echo();
    return input;
}

int menu::handleInput(string input) {
    if (input == "menu") {
        return 1;
    }
    if (input == "help") {
        return 2;
    }
    if (!h.is_number(input)) {
        return 3;
    }
    
    return 0;
}