use std::io::{self, Write};
mod negation;

fn main() {
    println!("Enter a formula");
    io::stdout().flush().unwrap();
    let mut input = String::new();

    if let Err(e) = io::stdin().read_line(&mut input) {
        println!("wrong input {}", e);
        return;
    }
    let nnf_result = negation::negation_normal_form(input.trim());
    println!("NNF formula: {}", nnf_result);
}