#include <iostream>
#include "sudoku.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    mySudoku.test();
    mySudoku.solve_all("easy50.txt", "easy");
    mySudoku.solve_all("top95.txt", "hard");
    mySudoku.solve_all("hardest.txt", "hardest");

    system("pause");
    return 0;
}