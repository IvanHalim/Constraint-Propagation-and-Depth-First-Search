#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iterator>
#include <cassert>
#include "sudoku.hpp"

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

/*
 * A utility function to check whether a string contains a particular substring
 */
bool string_contains(string str, string substring) {
    if (str.find(substring) != string::npos)
        return true;
    return false;
}

sudoku::sudoku() {
    digits = "123456789";
    rows = "ABCDEFGHI";
    cols = digits;
    squares = cross(rows, cols);

    /*
     * Creating vector<vector<string>> unitlist:
     *
     * unitlist = ([cross(rows, c) for c in cols] +
     *             [cross(r, cols) for r in rows] +
     *             [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
     */
    string rows_threes[3] = {"ABC", "DEF", "GHI"};
    string cols_threes[3] = {"123", "456", "789"};
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
     * Creating map<string, vector<vector<string>>> units:
     *
     * units = dict((s, [u for u in unitlist if s in u]) for s in squares)
     *
     *      can also be expressed as:
     *
     * units = {}
     * for s in squares:
     *     units[s] = []
     *     for u in unitlist:
     *         if s in u:
     *             units[s].append(u)
     */
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < unitlist.size(); j++) {
            if (vector_contains(unitlist[j], squares[i])) {
                units[squares[i]].push_back(unitlist[j]);
            }
        }
    }

    /*
     * Creating map<string, set<string>> peers:
     *
     * peers = dict((s, set(sum(units[s],[]))-set([s])) for s in squares)
     *
     *      can also be expressed as:
     *
     * peers = {}
     * for s in squares:
     *     peers[s] = set()
     *     for u in units[s]:
     *         for square in u:
     *             peers[s].add(square)
     *     peers[s].remove(s)
     */
    for (int i = 0; i < squares.size(); i++) {
        for (int j = 0; j < units[squares[i]].size(); j++) {
            for (int k = 0; k < units[squares[i]][j].size(); k++) {
                peers[squares[i]].insert(units[squares[i]][j][k]);
            }
        }
        peers[squares[i]].erase(squares[i]);
    }
}

void sudoku::display_unitlist() {
    for (int i = 0; i < unitlist.size(); i++) {
        cout << i + 1 << ": ";
        for (int j = 0; j < unitlist[i].size(); j++) {
            cout << unitlist[i][j] << ' ';
        }
        cout << endl;
    }
}

void sudoku::display_peers() {
    for (map<string, set<string>>::iterator i = peers.begin(); i != peers.end(); i++) {
        cout << i->first << ": ";
        for (set<string>::iterator j = (i->second).begin(); j != (i->second).end(); j++) {
            cout << *j << ' ';
        }
        cout << endl;
    }
}

void sudoku::display_units() {
    for (map<string, vector<vector<string>>>::iterator i = units.begin(); i != units.end(); i++) {
        cout << i->first << ':' << endl;
        for (int j = 0; j < (i->second).size(); j++) {
            for (int k = 0; k < (i->second)[j].size(); k++) {
                cout << (i->second)[j][k] << ' ';
            }
            cout << endl;
        }
    }
}

/*
 * def grid_values(grid):
 *     chars = [c for c in grid if c in digits or c in '0.']
 *     assert len(chars) == 81
 *     return dict(zip(squares, chars))
 */
map<string, string> sudoku::grid_values(string grid) {
    vector<string> chars;
    for (int i = 0; i < grid.length(); i++) {
        if (string_contains(digits, grid.substr(i, 1)) || string_contains("0.", grid.substr(i, 1))) {
            chars.push_back(grid.substr(i, 1));
        }
    }
    assert(chars.size() == squares.size());
    map<string, string> values;
    for (int i = 0; i < squares.size(); i++) {
        values[squares[i]] = chars[i];
    }
    return values;
}