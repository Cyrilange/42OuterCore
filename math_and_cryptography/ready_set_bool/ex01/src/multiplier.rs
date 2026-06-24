pub fn multiplier(mut a: u32, mut b: u32) -> u32
 {
	let mut result: u32 = 0;
	while b != 0 {
		
		if (b & 1) == 1 {
			let mut r: u32 = result;
			let mut y: u32 = a;
			while y != 0 {
				let carry: u32 = r & y;
				r = r ^ y;
				y = carry << 1;
			}

			result = r;
		}
		a <<= 1;
		b >>= 1;
	}
	result
 }

// Time Complexity: O(1) - Max 32 * 32 = 1024 operations (fixed u32 bit-width).
// Space Complexity: O(1) - Constant memory used, regardless of input size.


