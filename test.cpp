#include <iostream>
#include "sudoku.hpp"

using std::cin;

int main() {
    sudoku mySudoku;
    string grid1 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    mySudoku.solve(grid1);
    mySudoku.display_solution();

    return 0;
}