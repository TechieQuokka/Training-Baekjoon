use std::io::{self, BufRead};

fn main() {

    let stdin = io::stdin();
    let mut iterator = stdin.lock().lines();

    let first_line = iterator.next().unwrap().unwrap();
    let mut first_line_split = first_line.split_whitespace();
    let size: usize = first_line_split.next().unwrap().parse().unwrap();
    let target: i32 = first_line_split.next().unwrap().parse().unwrap();

    let second_line = iterator.next().unwrap().unwrap();
    let source: Vec<i32> = second_line
        .split_whitespace()
        .map(|s| s.parse().unwrap())
        .collect();

    let result = solution (&source, size, target);
    println! ("{}", result);
}

fn solution (source: &Vec<i32>, length: usize, target: i32) -> i32 {

    let mut result = 0;
    
    for first in 0..length-2 {
        for second in first+1..length-1 {
            for third in second+1..length {
                let sum = source[first] + source[second] + source[third];
                if sum <= target && sum > result {

                    result = sum;
                }
            }
        }
    }

    result
}