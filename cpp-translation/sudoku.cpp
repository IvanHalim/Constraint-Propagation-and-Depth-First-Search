#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cassert>
#include <cmath>
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
vector<string> cross(const string &A, const string &B) {
    vector<string> cross;
    for (auto a : A) {
        for (auto b : B) {
            string sq;
            sq += a;
            sq += b;
            cross.push_back(sq);
        }
    }
    return cross;
}

/*
 * A helper function to check whether a string vector contains a particular string
 */
bool vector_contains(const vector<string> &vec, const string &s) {
    for (auto const& i : vec) {
        if (i == s) {
            return true;
        }
    }
    return false;
}

/*
 * A helper function to check whether a string contains a particular substring
 */
bool string_contains(const string &str, const string &substring) {
    if (str.find(substring) != string::npos) {
        return true;
    } else {
        return false;
    }
}

/*
 * A helper function to erase a substring from a string
 */
string string_eliminate(string str, const string &substring) {
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
    for (int i = 0; i < leading_spaces; i++) {
        str.insert(0, " ");
    }
    for (int i = 0; i < trailing_spaces; i++) {
        str.append(" ");
    }
    return str;
}

/*
 * A helper function to find the maximum length of the values in the grid
 */
int find_max_length(const map<string, string> &values) {
    int max_length = 0;
    for (auto const& i : values) {
        if ((i.second).length() > max_length) {
            max_length = (i.second).length();
        }
    }
    return max_length;
}

/*
 * A helper function to find the square with the minimum number of possibilities
 */
string find_min_possibilities(const map<string, string> &values) {
    int min_length = 10;
    string min_square;
    for (auto const& i : values) {
        if ((i.second).length() < min_length && (i.second).length() > 1) {
            min_length = (i.second).length();
            min_square = i.first;
        }
    }
    return min_square;
}

/*
 * A helper function to check if a grid is solved
 */
bool solved(const map<string, string> &values) {
    for (auto const& i : values) {
        if ((i.second).length() != 1) {
            return false;
        }
    }
    return true;
}

/*
 * A helper function to create a horizontal line on a sudoku grid
 * given a single column width
 */
string create_line(int width, int size) {
    string line;
    for (int i = 0; i < pow(size, 2); i++) {
        for (int j = 0; j < width; j++) {
            line += "-";
        }
        if ((i + 1) % size == 0 && (i + 1) < pow(size, 2)) {
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
void sudoku::display(map<string, string> &values) {
    if (values["A1"] == "false") {
        cout << "**NO SOLUTION IS FOUND**" << endl << endl;
        return;
    }
    int width = 1 + find_max_length(values);
    string line = create_line(width, size);
    for (int i = 0; i < rows.length(); i++) {
        for (int j = 0; j < cols.length(); j++) {
            cout << center_string(values[squares[i*pow(size, 2)+j]], width);
            if ((j + 1) % size == 0 && (j + 1) < pow(size, 2)) {
                cout << "|";
            }
        }
        cout << endl;
        if ((i + 1) % size == 0 && (i + 1) < pow(size, 2)) {
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
map<string, string> sudoku::grid_values(const string &grid) {
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
    size = 3;
    digits = "123456789";
    rows = "ABCDEFGHI";
    cols = digits;
    squares = cross(rows, cols);

    /*
     * string rows_threes[3] = {"ABC", "DEF", "GHI"};
     * string cols_threes[3] = {"123", "456", "789"};
     */
    vector<string> rows_threes;
    vector<string> cols_threes;
    for (int i = 0; i < pow(size, 2); i += size) {
        rows_threes.push_back(rows.substr(i, size));
        cols_threes.push_back(cols.substr(i, size));
    }

    /*
     * Creating vector<vector<string> > unitlist:
     *
     * unitlist = ([cross(rows, c) for c in cols] +
     *             [cross(r, cols) for r in rows] +
     *             [cross(rs, cs) for rs in ('ABC','DEF','GHI') for cs in ('123','456','789')])
     */
    for (int i = 0; i < rows.length(); i++) {
        unitlist.push_back(cross(rows.substr(i, 1), digits));
    }
    for (int i = 0; i < digits.length(); i++) {
        unitlist.push_back(cross(rows, digits.substr(i, 1)));
    }
    for (auto const& rs : rows_threes) {
        for (auto const& cs : cols_threes) {
            unitlist.push_back(cross(rs, cs));
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
    for (auto const& s : squares) {
        for (auto const& u : unitlist) {
            if (vector_contains(u, s)) {
                units[s].push_back(u);
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
    for (auto const& s : squares) {
        for (auto const& u : units[s]) {
            for (auto square : u) {
                peers[s].insert(square);
            }
        }
        peers[s].erase(s);
    }

    // Since there is no input, initialize an empty grid
    // If the grid is empty then each square can be any number from 1 to 9
    for (auto const& s : squares) {
        input[s] = ".";
        solution[s] = digits;
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
bool sudoku::parse_grid(const string &grid) {
    for (auto const& s : squares) {
        solution[s] = digits;
    }
    input = grid_values(grid);
    for (auto const& i : input) {
        if (string_contains(digits, i.second) && !assign(solution, i.first, i.second)) {
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
bool sudoku::assign(map<string, string> &values, const string &s, const string &d) {
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
bool sudoku::eliminate(map<string, string> &values, const string &s, const string &d) {
    if (!string_contains(values[s], d)) {
        return true;
    }
    values[s] = string_eliminate(values[s], d);
    if (values[s].length() == 0) {
        return false;
    } else if (values[s].length() == 1) {
        string d2 = values[s];
        for (auto const& s2 : peers[s]) {
            if (!eliminate(values, s2, d2)) {
                return false;
            }
        }
    }
    for (auto const& u : units[s]) {
        vector<string> dplaces;
        for (auto const& s : u) {
            if (string_contains(values[s], d)) {
                dplaces.push_back(s);
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
    string s = find_min_possibilities(values);
    map<string, string> copy = values;
    for (int i = 0; i < values[s].length(); i++) {
        if (assign(values, s, values[s].substr(i, 1))) {
            if (search(values)) {
                return true;
            }
        }
        values = copy;
    }
    return false;
}

bool sudoku::solve(const string &grid) {
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

map<string, string> sudoku::get_input() {
    return input;
}

map<string, string> sudoku::get_parsed_grid() {
    return parsed_grid;
}

map<string, string> sudoku::get_solution() {
    return solution;
}