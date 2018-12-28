#include <iostream>
#include <chrono>
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
    cout << endl;

    string spawn_of_hell  = ".....6....59.....82....8....45........3........6..3.54...325..6..................";
    auto t1 = std::chrono::high_resolution_clock::now();
    mySudoku.solve(spawn_of_hell);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = t2 - t1;

    mySudoku.display_input();
    mySudoku.display_solution();
    cout << elapsed.count() << " secs" << endl << endl;

    system("pause");
    return 0;
}