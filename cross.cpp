#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

string concatenate(char a, char b) {
    return string() + a + b;
}

vector<string> cross(string A, string B) {
    vector<string> str;
    for (int i = 0; i < A.length(); i++) {
        for (int j = 0; j < B.length(); j++) {
            str.push_back(concatenate(A[i],B[j]));
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
        unitlist.push_back(cross(rows[i], digits));
    }
    for (int i = 0; i < digits.length(); i++) {
        unitlist.push_back(cross(rows, digits[i]));
    }
    string x[3] = {"ABC", "DEF", "GHI"};
    string y[3] = {"123", "456", "789"};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            unitlist.push_back(cross(x[i], y[j]));
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