use std::io::{self, BufRead, BufWriter, Write};

fn main() {
    let stdin = io::stdin();
    let mut buffer = String::new();
    stdin.lock().read_line(&mut buffer).expect("입력 오류");

    let number = buffer.trim().parse::<usize>().expect("유효한 숫자가 아닙니다.");

    let stdout = io::stdout();
    let mut writer = BufWriter::new(stdout.lock());

    for decrease in (1..=number).rev() {
        writeln!(writer, "{}", decrease).expect("출력 오류");
    }
}