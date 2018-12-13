#include <iostream>
#include "sudoku.hpp"

using std::cin;

int main() {
    sudoku mySudoku;
    string grid1 = "530070000600195000098000060800060003400803001700020006060000280000419005000080079";
    mySudoku.solve(grid1);
    mySudoku.display_solution();

    return 0;
}