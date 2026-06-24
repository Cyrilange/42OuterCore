pub fn eval_formula(formula: &str) -> bool {

	let mut stack: Vec<bool> = Vec::new();

	for token in formula.chars() {
		match token {
			'0' => stack.push(false),
			'1' => stack.push(true),
			'!' =>  { let a = stack.pop().unwrap();
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

	stack.pop().unwrap()

}


//The Time Complexity is O(n) (where $n$ is the total number of characters in the formula)
// because the program processes each character exactly once and performs fast, 
//constant-time O(1) operations on the stack.