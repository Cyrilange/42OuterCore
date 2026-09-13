
export function grayCode(n: number): number {
    return n ^ (n >> 1);
}

