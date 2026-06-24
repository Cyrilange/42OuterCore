
use std::io::{self,Write};

mod gray_code;

fn main() {
    print!("Enter a number : ");
    io::stdout().flush().unwrap();
    let mut input: String = String::new();

    if let Err(e) = io::stdin().read_line(&mut input) {
        println!("Input error {}", e);
        return ;
    }

    let num:u32 =  input.trim().parse().unwrap();

    let result = gray_code::gray_code(num);

    println!("{}", result);
}
