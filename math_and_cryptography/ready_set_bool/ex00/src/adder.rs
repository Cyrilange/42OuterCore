

pub fn adder(mut a: u32, mut b: u32) -> u32 {
    while b != 0 {
		let carry: u32 = a & b;  // add without carry
		a = a ^ b;  // compute carry
		b = carry << 1; // shift the carry to the left so it is added to the next higher bit.
	}
	a
}

// Time Complexity: O(1) -> Better than O(log n) because it is capped at 32 steps as u32
// Space Complexity: O(1) -> Modifies inputs with minimal extra memory.