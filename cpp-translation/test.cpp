#include <iostream>
#include <chrono>
#include "sudoku.hpp"

using std::cout;
using std::endl;

int main() {
    sudoku mySudoku;
    mySudoku.test();
    mySudoku.solve_all("../input/easy50.txt", "easy", 0.2);
    mySudoku.solve_all("../input/top95.txt", "hard", 0.2);
    mySudoku.solve_all("../input/hardest.txt", "hardest", 0.2);
    cout << endl;

    cout << "Solving diabolical puzzle...";
    string spawn_of_hell  = ".....6....59.....82....8....45........3........6..3.54...325..6..................";
    auto t1 = std::chrono::high_resolution_clock::now();
    mySudoku.solve(spawn_of_hell);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = t2 - t1;

    cout << endl << endl;
    mySudoku.display_input();
    mySudoku.display_parsed_grid();
    mySudoku.display_solution();
    cout << '(' << elapsed.count() << " seconds)" << endl << endl;

    system("pause");
    return 0;
}