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

/***************************************************************************************
                                    HELPER FUNCTIONS
***************************************************************************************/

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
 * A helper function to check whether a string vector contains a particular string
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
 * A helper function to check whether a string contains a particular substring
 */
bool string_contains(string str, string substring) {
    if (str.find(substring) != string::npos) {
        return true;
    } else {
        return false;
    }
}

/*
 * A helper function to erase a substring from a string
 */
string string_eliminate(string str, string substring) {
    string::size_type position = str.find(substring);
    if (position == string::npos) {
        return str;
    } else {
        return str.replace(position, substring.length(), "");
    }
}

/*
 * A helper function to center a string inside a given width
 */
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

/*
 * A helper function to find the maximum length of the values in the grid
 */
int find_max_length(map<string, string> values) {
    int max_length = 0;
    for (map<string, string>::iterator i = values.begin(); i != values.end(); i++) {
        if ((i->second).length() > max_length) {
            max_length = (i->second).length();
        }
    }
    return max_length;
}

/*
 * A helper function to find the square with the minimum number of possibilities
 */
string find_min_possibilities(map<string, string> values) {
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

/*
 * A helper function to check if a grid is solved
 */
bool solved(map<string, string> values) {
    for (map<string, string>::iterator i = values.begin(); i != values.end(); i++) {
        if ((i->second).length() != 1) {
            return false;
        }
    }
    return true;
}

/*
 * A helper function to create a horizontal line on a sudoku grid
 * given a single column width
 */
string create_line(int width) {
    string line;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < width; j++) {
            line += "-";
        }
        if (i == 2 || i == 5) {
            line += "+";
        }
    }
    return line;
}

/*
 * This function displays the values in a hash map as a sudoku grid
 *
 * def display(values):
 *     "Display these values as a 2-D grid."
 *     width = 1+max(len(values[s]) for s in squares)
 *     line = '+'.join(['-'*(width*3)]*3)
 *     for r in rows:
 *         print ''.join(values[r+c].center(width)+('|' if c in '36' else '') for c in cols)
 *         if r in 'CF':
 *             print line
 *     print
 */
void sudoku::display(map<string, string> values) {
    if (values["A1"] == "false") {
        cout << "**NO SOLUTION IS FOUND**" << endl;
        return;
    }
    int width = 1 + find_max_length(values);
    string line = create_line(width);
    for (int i = 0; i < rows.length(); i++) {
        for (int j = 0; j < cols.length(); j++) {
            cout << center_string(values[squares[i*9+j]], width);
            if (j+1 == 3 || j+1 == 6) {
                cout << "|";
            }
        }
        cout << endl;
        if (i == 2 || i == 5) {
            cout << line << endl;
        }
    }
    cout << endl;
}

/*
 * This function converts a string of values into a map of {square: char}
 * with '0' or '.' for empties.
 *
 * def grid_values(grid):
 *     "Convert grid into a dict of {square: char} with '0' or '.' for empties."
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

/***************************************************************************************
                            INITIALIZATION OF MEMBER VARIABLES
***************************************************************************************/

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

    // Since there is no input, initialize an empty grid
    for (int i = 0; i < squares.size(); i++) {
        input[squares[i]] = ".";
    }

    // If the grid is empty then each square can be any number from 1 to 9
    for (int i = 0; i < squares.size(); i++) {
        solution[squares[i]] = digits;
    }

    parsed_grid = solution;
}

/***************************************************************************************
                            PART I: CONSTRAINT PROPAGATION
***************************************************************************************/

/*
 * This function uses constraint propagation to compute all the possible numbers
 * in each square based on the initial input. You may think of 'propagation' as
 * a sort of chain reaction or a ripple effect where assigning or eliminating a number
 * may lead to the elimination of many other numbers because of the constraints.
 *
 * def parse_grid(grid):
 *     """Convert grid to a dict of possible values, {square:digits}, or
 *     return False if a contradiction is detected."""
 *     ## To start, every square can be any digit; then assign values from the grid.
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
            parsed_grid = solution;
            return false;
        }
    }
    parsed_grid = solution;
    return true;
}

/*
 * A function to assign a number to a square in the sudoku board
 * Assigning a number is equivalent to eliminating all the other possible numbers
 *
 * def assign(values, s, d):
 *     """Eliminate all the other values (except d) from values[s] and propagate.
 *     Return values, except return False if a contradiction is detected."""
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
 *     """Eliminate d from values[s]; propagate when values or places <= 2.
 *     Return values, except return False if a contradiction is detected."""
 *     if d not in values[s]:
 *         return values ## Already eliminated
 *     values[s] = values[s].replace(d,'')
 *     ## (1) If a square s is reduced to one value d2, then eliminate d2 from the peers.
 *     if len(values[s]) == 0:
 *         return False ## Contradiction: removed last value
 *     elif len(values[s]) == 1:
 *         d2 = values[s]
 *         if not all(eliminate(values, s2, d2) for s2 in peers[s]):
 *             return False
 *     ## (2) If a unit u is reduced to only one place for a value d, then put it there.
 *     for u in units[s]:
 *         dplaces = [s for s in u if d in values[s]]
 *         if len(dplaces) == 0:
 *             return False ## Contradiction: no place for this value
 *         elif len(dplaces) == 1:
 *             ## d can only be in one place in unit; assign it there
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

/***************************************************************************************
                            PART II: RECURSIVE SEARCH
***************************************************************************************/

/*
 * After some values have been eliminated, if there are still unsolved squares,
 * use a trial-and-error algorithm to solve the remaining squares
 *
 * def search(values):
 *     "Using depth-first search and propagation, try all possible values."
 *     if values is False:
 *         return False ## Failed earlier
 *     if all(len(values[s]) == 1 for s in squares):
 *         return values ## Solved!
 *     ## Chose the unfilled square s with the fewest possibilities
 *     n,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
 *     for d in values[s]:
 *         result = search(assign(values.copy(), s, d))
 *         if result: return result
 */
bool sudoku::search(map<string, string> &values) {
    if (values["A1"] == "false") {
        return false;
    }
    if (solved(values)) {
        return true;
    }
    string min_square = find_min_possibilities(values);
    map<string, string> copy = values;
    for (int i = 0; i < values[min_square].length(); i++) {
        if (assign(values, min_square, values[min_square].substr(i, 1))) {
            if (search(values)) {
                return true;
            }
        }
        values = copy;
    }
    return false;
}

bool sudoku::solve(string grid) {
    parse_grid(grid);
    if (!search(solution)) {
        solution["A1"] = "false";
        return false;
    }
    return true;
}

/***************************************************************************************
                                ADDITIONAL FUNCTIONS
***************************************************************************************/

void sudoku::display_input() {
    display(input);
}

void sudoku::display_parsed_grid() {
    display(parsed_grid);
}

void sudoku::display_solution() {
    display(solution);
}

map<string, string> sudoku::get_solution() {
    return solution;
}