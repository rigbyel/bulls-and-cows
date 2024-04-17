#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>

using namespace std;

class Host {
public:
    vector<char> num;
    int tries;
    int len;
    int base;

    bool initNumber(int length, int uBase);
    int handleInput(string input);
    bool checkNumber(vector<char>& digits);



    void newGame();
};

#endif