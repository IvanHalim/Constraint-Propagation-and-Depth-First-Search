#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::substr;
using std::vector;

vector<string> cross(string A, string B) {
    vector<string> str(A.length() * B.length());
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
    vector<string> squares = cross(rows, cols);
    vector<vector<string> > unitlist;
    for (int i = 0; i < rows.length(); i++) {
        unitlist.push_back(cross(string() + rows[i], digits));
    }
    for (int i = 0; i < digits.length(); i++) {
        unitlist.push_back(cross(rows, string() + digits[i]));
    }
    string x[3] = {"ABC", "DEF", "GHI"};
    string y[3] = {"123", "456", "789"};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            unitlist.push_back(cross(string() + x[i], string() + y[j]));
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