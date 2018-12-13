#include <iostream>
#include "sudoku.hpp"

using std::cin;

int main() {
    string grid1;
    cin >> grid1;
    sudoku mySudoku;
    mySudoku.parse_grid(grid1);
    mySudoku.display_solution();

    return 0;
}