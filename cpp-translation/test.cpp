#include <iostream>
#include "sudoku.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    string grid = "000000000000003085001020000000507000004000100090000000500000073002010000000040009";
    mySudoku.solve(grid);
    mySudoku.display_input();
    mySudoku.display_parsed_grid();
    mySudoku.display_solution();
    grid = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    mySudoku.solve(grid);
    mySudoku.display_input();
    mySudoku.display_parsed_grid();
    mySudoku.display_solution();

    system("pause");
    return 0;
}