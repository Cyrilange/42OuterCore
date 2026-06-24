use std::io::{self, Write};
mod adder;

fn main() {
    print!("enter two numbers: ");
    io::stdout().flush().unwrap();

    let mut input = String::new();

    if let Err(e) = io::stdin().read_line(&mut input) {
        println!("input error: {}", e);
        return;
    }

    let parts: Vec<&str> = input.trim().split_whitespace().collect();

    if parts.len() < 2 {
        println!("error: need 2 numbers");
        return;
    }

    let a = match parts[0].parse::<u32>() {
        Ok(n) => n,
        Err(_) => {
            println!("error: first number invalid");
            return;
        }
    };

    let b = match parts[1].parse::<u32>() {
        Ok(n) => n,
        Err(_) => {
            println!("error: second number invalid");
            return;
        }
    };

    let result = adder::adder(a, b);

    println!("{}", result);
}


//if you want to check error fast you have unwrap(), but Ok et Err are like try catch