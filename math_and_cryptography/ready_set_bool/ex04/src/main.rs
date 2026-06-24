use std::io::{self, Write};
mod truth_table;

fn main() {
    println!("Enter a formula");
    io::stdout().flush().unwrap();
    let mut input = String::new();

    if let Err(e) = io::stdin().read_line(&mut input) {
        println!("wrong input {}", e);
        return ;
    }
    truth_table::print_truth_table(&input.trim());
}
