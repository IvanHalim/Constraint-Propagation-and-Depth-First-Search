#include "sudoku.hpp"

int main() {
    string grid1 = "003020600900305001001806400008102900700000008006708200002609500800203009005010300";
    sudoku mySudoku;
    mySudoku.display(mySudoku.parse_grid(grid1));

    return 0;
}