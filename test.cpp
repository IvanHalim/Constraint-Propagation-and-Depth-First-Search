#include <iostream>
#include "sudoku.hpp"

using std::cin;

int main() {
    sudoku mySudoku;
    string grid1 = "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
    mySudoku.solve(grid1);
    mySudoku.display_solution();

    return 0;
}