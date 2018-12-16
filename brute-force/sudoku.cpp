#include <iostream>
#include <string>
#include <sstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::istringstream;

struct coordinate {
    int x;
    int y;
};

coordinate create_coordinate(int x, int y) {
    coordinate c;
    c.x = x;
    c.y = y;
    return c;
}

bool check(int sudoku[9][9], coordinate now, int val) {
    //===== CHECK BOX =====
    int box_index_x = now.x / 3;
    int box_index_y = now.y / 3;
    for (int i = 3 * box_index_x; i < 3 * box_index_x + 3; i++) {
        for (int j = 3 * box_index_y; j < 3 * box_index_y + 3; j++) {
            if (sudoku[i][j] == val) {
                return false;
            }
        }
    }


    //===== CHECK ROW =====
    for (int i = 0; i < 9; i++) {
        if (sudoku[now.x][i] == val) {
            return false;
        }
    }

    //===== CHECK COLUMN =====
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][now.y] == val) {
            return false;
        }
    }

    return true;
}

coordinate next_coordinate(coordinate c) {
    if (c.y < 9) {
        c.y++;
    }
    if (c.y == 9) {
        c.y = 0;
        c.x++;
    }
    return c;
}

void copy(int copy[9][9], int ori[9][9]) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            copy[i][j] = ori[i][j];
        }
    }
}

void print(int sudoku[9][9]) {
    string line;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 2; j++) {
            line += "-";
        }
        if (i == 2 || i == 5) {
            line += "+";
        }
    }
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << sudoku[i][j] << ' ';
            if (j == 2 || j == 5) {
                cout << '|';
            }
        }
        cout << endl;
        if (i == 2 || i == 5) {
            cout << line << endl;
        }
    }
    cout << endl;
}

bool solve(int sudoku[9][9], coordinate now) {
    if (now.x == 9) {
        return true;
    }
    if (sudoku[now.x][now.y] == 0) {
        for (int i = 1; i <= 9; i++) {
            if (check(sudoku, now, i)) {
                int arr[9][9];
                copy(arr, sudoku);
                sudoku[now.x][now.y] = i;
                if (solve(sudoku, next_coordinate(now))) {
                    return true;
                }
                copy(sudoku, arr);
            }
        }
    } else if (solve(sudoku, next_coordinate(now))) {
        return true;
    }
    return false;
}

void parse_grid(int sudoku[9][9], string grid) {
    for (int i = 0; i < grid.length(); i++) {
        istringstream ss(grid.substr(i, 1));
        ss >> sudoku[i/9][i%9];
    }
}

int main() {
    int sudoku[9][9];
    string grid = "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
    parse_grid(sudoku, grid);
    solve(sudoku, create_coordinate(0, 0));
    print(sudoku);

    system("pause");
    return 0;
}