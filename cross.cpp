#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

vector<string> cross(string A, string B) {
    vector<string> str;
    for (int i = 0; i < A.length(); i++) {
        for (int j = 0; j < B.length(); j++) {
            str.push_back(A.substr(i, 1) + B.substr(j, 1));
        }
    }

    return str;
}

int main() {
    string digits = "123456789";
    string rows = "ABCDEFGHI";
    string cols = digits;
    string rows_threes[3] = {"ABC", "DEF", "GHI"};
    string cols_threes[3] = {"123", "456", "789"};
    vector<string> squares = cross(rows, cols);
    vector<vector<string> > unitlist;
    for (int i = 0; i < 9; i++) {
        unitlist.push_back(cross(rows.substr(i, 1), digits));
    }
    for (int i = 0; i < 9; i++) {
        unitlist.push_back(cross(rows, digits.substr(i, 1)));
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            unitlist.push_back(cross(rows_threes[i], cols_threes[j]));
        }
    }

    for (int i = 0; i < unitlist.size(); i++) {
        for (int j = 0; j < 9; j++) {
            cout << unitlist[i][j] << ' ';
        }
        cout << endl;
    }

    return 0;
}