#include <iostream>
#include "sudoku.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    string grid1 = "800000000003600000070090200050007000000045700000100030001000068008500010090000400";
    mySudoku.parse_grid(grid1);
    mySudoku.display_input();
    cout << endl;
    mySudoku.display_solution();
    cout << endl;
    mySudoku.solve(grid1);
    mySudoku.display_solution();
    cout << endl;
    grid1 = "4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......";
    mySudoku.parse_grid(grid1);
    mySudoku.display_input();
    cout << endl;
    mySudoku.display_solution();
    cout << endl;
    mySudoku.solve(grid1);
    mySudoku.display_solution();
    cout << endl;

    return 0;
}