import { my_pow , my_sqrt} from "./utils_math.js"
import {parseTerm, separate,tokenise, parseterms, reduceEquation,trie_degree,formatOutput } from "./utils.parsing.js"


export function getDegree(terms) {
	let max = 0;
	for(let i = 0; i < terms.length; i++) {
		if(terms[i].degree > max &&  terms[i].coef !== 0) {
			max = terms[i].degree;
		}
	}
	return max;
}


export function degree1(terms) {
    let a = 0;
    let b = 0;
    for(let i = 0; i < terms.length; i++) {
        if(terms[i].degree === 1) { a = terms[i].coef; }
        if(terms[i].degree === 0) { b = terms[i].coef; }
    }
    return -b / a;
}

export function degree2(terms) {
	let a = 0;
	let b = 0;
	let c = 0;
	for(let i = 0; i < terms.length; i++) {
		if(terms[i].degree === 2) { a = terms[i].coef; }  // a = degree 2
		if(terms[i].degree === 1) { b = terms[i].coef; }  // b = degree 1
		if(terms[i].degree === 0) { c = terms[i].coef; }  // c = degree 0
    }
	let delta = my_pow(b, 2) - 4 * a * c;  
		if(delta > 0) {
			console.log("Discriminant is strictly positive, the two solutions are:");
			let x1 = (-b + my_sqrt(delta)) / (2 * a);
			let x2 = (-b - my_sqrt(delta)) / (2 * a);
			
			console.log(x1.toFixed(9));
			console.log(x2.toFixed(9));
		}
		else if (delta == 0) {
			let x = -b / (2 * a);
			console.log(x);
		}
		else if (delta < 0){
			console.log("Discriminant is strictly negative, the two complex solutions are:");
			let real = -b / (2 * a);
			let imag = my_sqrt(-delta) / (2 * a);	
			console.log(real + " + " + imag + ' * i');
			console.log(real + " - " + imag + ' * i');
		}
	return delta;

}