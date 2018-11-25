#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>
#include <vector>
#include <map>
#include <set>

using std::string;
using std::vector;
using std::map;
using std::set;

class sudoku {
    private:
        string digits;
        string rows;
        string cols;
        vector<string> squares;
        vector<vector<string> > unitlist;
        map<string, vector<vector<string> > > units;
        map<string, set<string> > peers;
        map<string, string> grid_values(string);
        bool assign(map<string, string>&, string, string);
        bool eliminate(map<string, string>&, string, string);
    public:
        sudoku();
        map<string, string> parse_grid(string);
        void display(map<string, string>);
};
#endif