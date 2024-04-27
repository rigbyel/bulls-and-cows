#ifndef HOST_H
#define HOST_H

#include <string>
#include <vector>

using namespace std;

class Host {
private:
    vector<char> num;
    int len;
    int base;

    bool initNumber(int length, int uBase);
    int handleInput(string input);
    bool checkNumber(vector<char>& digits);
    bool is_number(std::string& s);

public:
    int newGame();
};

#endif