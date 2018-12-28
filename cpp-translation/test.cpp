#include <iostream>
#include "sudoku.hpp"

using std::cin;
using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    mySudoku.test();
    mySudoku.solve_all("../input/easy50.txt", "easy");
    mySudoku.solve_all("../input/top95.txt", "hard");
    mySudoku.solve_all("../input/hardest.txt", "hardest");

    system("pause");
    return 0;
}