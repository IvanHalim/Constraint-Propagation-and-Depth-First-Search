#include <iostream>
#include "sudoku.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    string grid1 = "000000000000003085001020000000507000004000100090000000500000073002010000000040009";
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

    system("pause");
    return 0;
}