#include <iostream>
#include <string>

using namespace std;

string gen(int n) {
    string str = "";
    int counter = n;
    while (counter-- > 0)
        str += "(";
    while (n-- > 0)
        str += ")";
    return str;
}

string next_str(string str) {
    int counter_open(0);
    int counter_close(0);
    for (int i = str.size() - 1; i >= 0; i--) {
        if (str[i] == '(') {
            counter_open++;
            if (counter_close > counter_open) break;
        }
        else counter_close++;
    }
    str.erase(str.end() - counter_open - counter_close, str.end());

    if (str == "") return "";
    else str += ")";
    for (int i = 0; i < counter_open; i++) {
        str += "(";
    }
    for (int i = 0; i < counter_close - 1; i++) {
        str += ")";
    }
    return str;
}