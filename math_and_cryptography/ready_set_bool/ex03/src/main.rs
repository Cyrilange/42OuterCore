use std::io::{self, Write};
mod bool_eval;

fn main() {
    println!("Enter a formula");
    io::stdout().flush().unwrap();
    let mut input = String::new();

    if let Err(e) = io::stdin().read_line(&mut input) {
        println!("wrong input {}", e);
        return ;
    }
  

    let _result = bool_eval::eval_formula(&input.trim());
    println!("the result : {}", _result);
}


/*

exemple :

println!("{}", eval_formula("10&"));
// false
println!("{}", eval_formula("10|"));
// true
println!("{}", eval_formula("11>"));
// true
println!("{}", eval_formula("10="));
// false
println!("{}", eval_formula("1011||="));
// true

console :

 valgrind cargo run
==28097== Memcheck, a memory error detector
==28097== Copyright (C) 2002-2022, and GNU GPL'd, by Julian Seward et al.
==28097== Using Valgrind-3.19.0 and LibVEX; rerun with -h for copyright info
==28097== Command: cargo run
==28097== 
    Finished `dev` profile [unoptimized + debuginfo] target(s) in 0.00s
     Running `target/debug/ex03`
Enter a formula
101|^
the result : false

*/