use std::collections::{HashMap};

#[derive(Debug)]
struct context {
    cols:       Vec<char>,
    rows:       Vec<char>,
    squares:    Vec<String>,
    unitlist:   Vec<Vec<String>>,
    units:      HashMap<String, Vec<Vec<String>>>,
    peers:      HashMap<String, Vec<String>>
}

fn cross(A: &[char], B: &[char]) -> Vec<String> {
    let mut cross : Vec<String> = Vec::new();
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

fn grid_values(grid: &str, ctx: &context) -> HashMap<String, Vec<char>> {
    let mut chars : Vec<Vec<char>> = Vec::new();
    for c in grid.chars() {

    }
    assert_eq!(chars.len(), 81);
    let grid_val : HashMap<String, Vec<char>> =
        ctx.squares.iter().cloned().zip(chars.into_iter()).collect();
    grid_val
}

fn parse_grid(grid: &str, ctx: &context) -> HashMap<String, Vec<char>> {
    let mut values : HashMap<String, Vec<char>> = HashMap::new();
}