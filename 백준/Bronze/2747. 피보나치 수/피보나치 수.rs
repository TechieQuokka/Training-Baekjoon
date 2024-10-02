use std::io;

fn fibonacci (memo: &mut Vec<i32>, number: i32) -> i32 {

    if memo[number as usize] != 0 {

        memo[number as usize]
    }
    else if number < 2 {
        number
    }
    else {
        memo[number as usize] = fibonacci (memo, number - 1) + fibonacci (memo, number - 2);
        memo[number as usize]
    }
}

fn main() {

    let mut input = String::new();

    io::stdin().read_line(&mut input).expect("");

    let mut iterate = input.trim().split_whitespace();
    let number: i32 = iterate.next().unwrap().parse().expect("");

    let mut memo: Vec<i32> = vec!(0; (number + 1) as usize);
    let result: i32 = fibonacci (&mut memo, number);
    println! ("{}", result)
}