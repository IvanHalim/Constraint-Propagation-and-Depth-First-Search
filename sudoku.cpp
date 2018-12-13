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
    if (str.find(substring) != string::npos) {
        return true;
    } else {
        return false;
    }
}

/*
 * A utility function to erase a substring from a string
 */
string string_eliminate(string str, string substring) {
    string::size_type position = str.find(substring);
    if (position == string::npos) {
        return str;
    } else {
        return str.replace(position, substring.length(), "");
    }
}

string center_string(string str, int width) {
    int leading_spaces = (width - str.length()) / 2;
    int trailing_spaces = width - str.length() - leading_spaces;
    string centered;
    for (int i = 0; i < leading_spaces; i++) {
        centered += " ";
    }
    centered += str;
    for (int i = 0; i < trailing_spaces; i++) {
        centered += " ";
    }
    return centered;
}

int find_max_length(map<string, string> values) {
    int max_length = 0;
    for (map<string, string>::iterator i = values.begin(); i != values.end(); i++) {
        if ((i->second).length() > max_length) {
            max_length = (i->second).length();
        }
    }
    return max_length;
}

string find_min_possibilities(map<string, string> &values) {
    int min_length = 10;
    string min_square;
    for (map<string, string>::iterator i = values.begin(); i != values.end(); i++) {
        if ((i->second).length() < min_length && (i->second).length() > 1) {
            min_length = (i->second).length();
            min_square = i->first;
        }
    }
    return min_square;
}

bool solved(map<string, string> values) {
    for (map<string, string>::iterator i = values.begin(); i != values.end(); i++) {
        if ((i->second).length() != 1) {
            return false;
        }
    }
    return true;
}

sudoku::sudoku() {
    digits = "123456789";
    rows = "ABCDEFGHI";
    cols = digits;
    squares = cross(rows, cols);

    /*
     * Creating vector<vector<string> > unitlist:
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
     * Creating map<string, vector<vector<string> > > units:
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
     * Creating map<string, set<string> > peers:
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

    for (int i = 0; i < squares.size(); i++) {
        input[squares[i]] = ".";
    }

    for (int i = 0; i < squares.size(); i++) {
        solution[squares[i]] = digits;
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
        if (string_contains(digits, grid.substr(i, 1))) {
            chars.push_back(grid.substr(i, 1));
        } else if (string_contains("0.", grid.substr(i, 1))) {
            chars.push_back(".");
        }
    }
    assert(chars.size() == squares.size());
    map<string, string> grid_val;
    for (int i = 0; i < squares.size(); i++) {
        grid_val[squares[i]] = chars[i];
    }
    return grid_val;
}

/*
 * def parse_grid(grid):
 *     values = dict((s, digits) for s in squares)
 *     for s,d in grid_values(grid).items():
 *         if d in digits and not assign(values, s, d):
 *             return False ## (Fail if we can't assign d to square s.)
 *     return values
 */
bool sudoku::parse_grid(string grid) {
    for (int i = 0; i < squares.size(); i++) {
        solution[squares[i]] = digits;
    }
    input = grid_values(grid);
    for (map<string, string>::iterator i = input.begin(); i != input.end(); i++) {
        if (string_contains(digits, i->second) && !assign(solution, i->first, i->second)) {
            solution["A1"] = "false";
            return false;
        }
    }
    return true;
}

/*
 * def assign(values, s, d):
 *     other_values = values[s].replace(d, '')
 *     if all(eliminate(values, s, d2) for d2 in other_values):
 *         return values
 *     else:
 *         return False
 */
bool sudoku::assign(map<string, string> &values, string s, string d) {
    string other_values = string_eliminate(values[s], d);
    for (int i = 0; i < other_values.length(); i++) {
        string d2 = other_values.substr(i, 1);
        if (!eliminate(values, s, d2)) {
            return false;
        }
    }
    return true;
}

/*
 * def eliminate(values, s, d):
 *     if d not in values[s]:
 *         return values
 *     values[s] = values[s].replace(d,'')
 *     if len(values[s]) == 0:
 *         return False
 *     elif len(values[s]) == 1:
 *         d2 = values[s]
 *         if not all(eliminate(values, s2, d2) for s2 in peers[s]):
 *             return False
 *     for u in units[s]:
 *         dplaces = [s for s in u if d in values[s]]
 *         if len(dplaces) == 0:
 *             return False
 *         elif len(dplaces) == 1:
 *             if not assign(values, dplaces[0], d):
 *                 return False
 *     return values
 */
bool sudoku::eliminate(map<string, string> &values, string s, string d) {
    if (!string_contains(values[s], d)) {
        return true;
    }
    values[s] = string_eliminate(values[s], d);
    if (values[s].length() == 0) {
        return false;
    } else if (values[s].length() == 1) {
        string d2 = values[s];
        for (set<string>::iterator i = peers[s].begin(); i != peers[s].end(); i++) {
            if (!eliminate(values, *i, d2)) {
                return false;
            }
        }
    }
    for (int i = 0; i < units[s].size(); i++) {
        vector<string> dplaces;
        for (int j = 0; j < units[s][i].size(); j++) {
            if (string_contains(values[units[s][i][j]], d)) {
                dplaces.push_back(units[s][i][j]);
            }
        }
        if (dplaces.size() == 0) {
            return false;
        } else if (dplaces.size() == 1) {
            if (!assign(values, dplaces[0], d)) {
                return false;
            }
        }
    }
    return true;
}

/*
 * def display(values):
 *     width = 1+max(len(values[s]) for s in squares)
 *     line = '+'.join(['-'*(width*3)]*3)
 *     for r in rows:
 *         print ''.join(values[r+c].center(width)+('|' if c in '36' else '') for c in cols)
 *         if r in 'CF':
 *             print line
 *     print
 */
void sudoku::display(map<string, string> values) {
    int width = 1 + find_max_length(values);
    string line;
    for (int i = 0; i < rows.length(); i++) {
        for (int j = 0; j < width; j++) {
            line += "-";
        }
        if (i+1 == 3 || i+1 == 6) {
            line += "+";
        }
    }
    for (int i = 0; i < rows.length(); i++) {
        for (int j = 0; j < cols.length(); j++) {
            cout << center_string(values[squares[i*9+j]], width);
            if (j+1 == 3 || j+1 == 6) {
                cout << "|";
            }
        }
        cout << endl;
        if (i+1 == 3 || i+1 == 6) {
            cout << line << endl;
        }
    }
}

void sudoku::display_input() {
    display(input);
}

void sudoku::display_solution() {
    display(solution);
}

/*
 * def search(values):
 *     if values is False:
 *         return False
 *     if all(len(values[s]) == 1 for s in squares):
 *         return values
 *     ## Chose the unfilled square s with the fewest possibilities
 *     n,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
 *     return some(search(assign(values.copy(), s, d))
 *                for d in values[s])
 */
bool sudoku::search(map<string, string> &values) {
    if (values["A1"] == "false") {
        return false;
    } else if (solved(values)) {
        return true;
    }
    string min_square = find_min_possibilities(values);
    map<string, string> copy = values;
    for (int i = 0; i < values[min_square].length(); i++) {
        values = copy;
        if(assign(values, min_square, values[min_square].substr(i, 1))) {
            if (search(values)) {
                return true;
            }
        }
    }
    values["A1"] = "false";
    return false;
}

bool sudoku::solve(string grid) {
    parse_grid(grid);
    return search(solution);
}