fn eval_formula(formula: &str, vars: &[bool; 26]) -> bool {
    let mut stack: Vec<bool> = Vec::new();

    for token in formula.chars() {
        match token {
            'A'..='Z' => {
                let index = (token as usize) - ('A' as usize);
                stack.push(vars[index]);
            }
            '0' => stack.push(false),
            '1' => stack.push(true),
            '!' => { 
                let a = stack.pop().unwrap();
                stack.push(!a);
            }
            '&' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a && b);
            }
            '|' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a || b);
            }
            '^' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a != b);
            }
            '>' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(!a || b);
            }
            '=' => {
                let b = stack.pop().unwrap();
                let a = stack.pop().unwrap();
                stack.push(a == b);
            }
            ' ' => continue,
            _ => panic!("the Formula you enter does not exist"),
        }
    }
	if stack.len() != 1 {
        panic!("The formula is invalid (too many variables or missing operators).");
    }
    stack.pop().unwrap()
}

pub fn print_truth_table(formula: &str) {
    let mut find_letter = Vec::new();
    for char in formula.chars() {
        if char.is_ascii_uppercase() && !find_letter.contains(&char) {
            find_letter.push(char); 
        }
    }
    find_letter.sort();

    let size = find_letter.len();
    for letter in &find_letter {
        print!("| {} ", letter);
    }
    println!("| = |");
    for _ in 0..=size { print!("|---"); } println!("|");
    let total_rows = 1 << size;
    for row in 0..total_rows {
        let mut current_letter = [false; 26];

        for i in 0..size {
            let bit = (row >> (size - 1 - i)) & 1;
            let val_bool = bit == 1;
            let var_char = find_letter[i];
            let index = (var_char as usize) - ('A' as usize); 
            current_letter[index] = val_bool;

            print!("| {} ", if val_bool { "1" } else { "0" });
        }
        let res = eval_formula(formula, &current_letter); 
        println!("| {} |", if res { "1" } else { "0" });
    }
}