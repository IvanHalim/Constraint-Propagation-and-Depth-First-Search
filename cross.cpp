#include <iostream>
#include <string>
#include <vector>
#include <map>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;

/*
 * def cross(A, B):
 *     return [a+b for a in A for b in B]
 */
vector<string> cross(string A, string B) {
    vector<string> str;
    for (int i = 0; i < A.length(); i++) {
        for (int j = 0; j < B.length(); j++) {
            str.push_back(A.substr(i, 1) + B.substr(j, 1));
        }
    }
    return str;
}

/*
 * A utility function to check whether a string vector contains a particular string
 */
bool vector_contains(vector<string> u, string s) {
    for (int i = 0; i < u.size(); i++) {
        if (u[i] == s) {
            return true;
        }
    }
    return false;
}

int main() {
    string digits = "123456789";
    string rows = "ABCDEFGHI";
    string cols = digits;
    vector<string> squares = cross(rows, cols);

    /* unitlist = ([cross(rows, c) for c in cols] +
     *     [cross(r, cols) for r in rows] +
     *     [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
     */
    string rows_threes[3] = {"ABC", "DEF", "GHI"};
    string cols_threes[3] = {"123", "456", "789"};
    vector<vector<string>> unitlist;
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

    map<string, vector<vector<string>>> units;
    for (int i = 0; i < 81; i++) {
        for (int j = 0; j < 27; j++) {
            if (vector_contains(unitlist[j], squares[i])) {
                units[squares[i]].push_back(unitlist[j]);
            }
        }
    }

    return 0;
}