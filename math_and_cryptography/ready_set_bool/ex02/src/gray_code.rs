pub fn gray_code(n: u32) -> u32 {
	return n  ^ (n >> 1);
}

//Time Complexity: $O(1)$ because bitwise operations (^ and >>) on a fixed-width u32 take a constant, single CPU cycle.

//Space Complexity: $O(1)$ because the calculation is done directly in-place without allocating any extra memory.