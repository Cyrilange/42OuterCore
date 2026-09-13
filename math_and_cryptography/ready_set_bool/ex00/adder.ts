export function adder(a: number, b: number): number {
    while (b !== 0) {
        let carry: number = a & b;

        a = a ^ b;

        b = carry << 1;
    }

    return a;
}

