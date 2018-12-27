use std::collections::{HashMap};

#[derive(Debug)]
struct sudoku {
    cols:       Vec<char>,
    rows:       Vec<char>,
    squares:    Vec<String>,
    unitlist:   Vec<Vec<String>>,
    units:      HashMap<String, Vec<Vec<String>>>,
    peers:      HashMap<String, Vec<String>>
}

fn cross(A: &[char], B: &[char]) -> Vec<String> {
    let mut cross = Vec::new();
    for a in A {
        for b in B {
            let mut sq = String::new();
            sq.push(*a);
            sq.push(*b);
            cross.push(sq)
        }
    }
    cross
}

fn grid_values(grid: &str, )