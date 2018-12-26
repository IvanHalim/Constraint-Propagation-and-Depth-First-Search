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
        //Variables
        int                                     size;
        string                                  digits;
        string                                  rows;
        string                                  cols;
        vector<string>                          squares;
        vector<vector<string> >                 unitlist;
        map<string, vector<vector<string> > >   units;
        map<string, set<string> >               peers;
        map<string, string>                     input;
        map<string, string>                     parsed_grid;
        map<string, string>                     solution;

        //Helper functions
        map<string, string>     grid_values(string);
        bool                    parse_grid(string);
        bool                    assign(map<string, string>&, string, string);
        bool                    eliminate(map<string, string>&, string, string);
        void                    display(map<string, string>&);
        bool                    search(map<string, string>&);
    public:
        sudoku();
        bool                    solve(string);
        void                    display_input();
        void                    display_parsed_grid();
        void                    display_solution();
        map<string, string>     get_input();
        map<string, string>     get_parsed_grid();
        map<string, string>     get_solution();
};
#endif