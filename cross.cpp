#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>

using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::map;
using std::set;

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

    /*
     * unitlist = ([cross(rows, c) for c in cols] +
     *             [cross(r, cols) for r in rows] +
     *             [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
     */
    string rows_threes[3] = {"ABC", "DEF", "GHI"};
    string cols_threes[3] = {"123", "456", "789"};
    vector<vector<string>> unitlist;
    for (int i = 0; i < rows.length(); i++) {
        unitlist.push_back(cross(rows.substr(i, 1), digits));
    }
    for (int i = 0; i < digits.length(); i++) {
        unitlist.push_back(cross(rows, digits.substr(i, 1)));
    }
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            unitlist.push_back(cross(rows_threes[i], cols_threes[j]));
        }
    }

    /*
     * units = dict((s, [u for u in unitlist if s in u]) for s in squares)
     *
     *      can also be expressed as:
     *
     * units = {}
     * for s in squares:
     *     for u in unitlist:
     *         if s in u:
     *             if s not in units:
     *                 units[s] = []
     *             units[s].append(u)
     */
    map<string, vector<vector<string>>> units;
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < unitlist.size(); j++) {
            if (vector_contains(unitlist[j], squares[i])) {
                units[squares[i]].push_back(unitlist[j]);
            }
        }
    }

    map<string, set<string>> peers;
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < units[squares[i]].size(); j++) {
            for (int k = 0; k < units[squares[i]][j].size(); k++) {
                peers[squares[i]].insert(units[squares[i]][j][k]);
            }
            peers[squares[i]].erase(squares[i]);
        }
    }

    for (map<string, set<string>>::iterator i = peers.begin(); i != peers.end(); i++) {
        cout << i->first << ": ";
        for (set<string>::iterator j = (i->second).begin(); j != (i->second).end(); j++) {
            cout << *j << ' ';
        }
        cout << endl;
    }

    return 0;
}