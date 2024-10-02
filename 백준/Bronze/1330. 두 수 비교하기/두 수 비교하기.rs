use std::io;

fn main() {

    let mut input = String::new();

    io::stdin().read_line(&mut input).expect("");

    let mut iterate = input.trim().split_whitespace();
    let left: i32 = iterate.next().unwrap().parse().expect("");
    let right: i32 = iterate.next().unwrap().parse().expect("");

    if left == right {
        println!("==");
    }
    else if left < right {
        println!("<");
    }
    else {
        println!(">");
    }
}