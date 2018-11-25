#include "sudoku.hpp"

int main() {
    string grid1 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    sudoku mySudoku;
    mySudoku.display(mySudoku.parse_grid(grid1));

    return 0;
}