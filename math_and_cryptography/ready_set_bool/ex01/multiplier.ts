
import {adder} from "../ex00/adder"

export function multiplier(a: number, b: number): number {
    let result: number = 0;

    while (b > 0) {
        result = adder(result, a);
        b--;
    }

    return result;
}

