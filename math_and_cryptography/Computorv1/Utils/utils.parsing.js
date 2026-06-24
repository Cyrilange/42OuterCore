import { my_abs } from "./utils_math.js";

export function parseTerm(term) {
	if(!term.includes("*")) {
        return { coef: parseFloat(term.trim()), degree: 0 };
    }
	const parts = term.split("*");
	const coef = parseFloat(parts[0].trim().replace(" ", ""));
	const degree = parseInt(parts[1].trim().split("^")[1].replace(" ", ""));
	return { coef, degree };
  }


export function separate(term) {
	const part = term.split("=");
	if (part.length !== 2) {
		console.log("Error: Term does not respect the form a ∗ ^xp");
		console.log("exemple of accepted terms : 5 * X^0 + 4 * X^1 = 4 * X^0");
        process.exit(1);
	}
	const left = part[0].trim();
	const right = part[1].trim();
	if (left === "" || right === "") {
        console.log("Error: Term does not respect the form a ∗ ^xp");
		console.log("exemple of accepted terms : 5 * X^0 + 4 * X^1 = 4 * X^0");
        process.exit(1);
    }
	return { left , right};
}
export function tokenise(term) {
	let current = "";
	let result = [];
	for(let i = 0; i < term.length; i++) {
		if(term[i] == ("+") || term[i] == ("-")) {
			 if(current.trim() !== "") {result.push(current.trim());}
			if(term[i] == '+') {
				current = "";
			} else if(term[i] == "-") {
				current = "-";
			}
		} else {
			current += term[i];
		}
	}
	result.push(current.trim());
	return result;
}

export function parseterms(token) {
	let result = [];
	for(let i = 0; i < token.length; i++) {
		result.push(parseTerm(token[i]));
	}
		return result;
}

export function reduceEquation(terms) {
	const {left, right} = separate(terms);
	const leftTokens = tokenise(left);
	const rightToken = tokenise(right);
	const leftTerms = parseterms(leftTokens);
	const rightTerms = parseterms(rightToken);
	for(let i = 0; i < rightTerms.length; i++) {
		rightTerms[i].coef = rightTerms[i].coef * -1;
		
	}
	for(let i = 0; i < rightTerms.length; i++) {
		leftTerms.push(rightTerms[i]);
	}
	for(let i = 0; i < leftTerms.length; i++) {
		for(let j = i + 1; j < leftTerms.length; j++) {
			if(leftTerms[i].degree == leftTerms[j].degree) {
				leftTerms[i].coef = leftTerms[i].coef + leftTerms[j].coef;
				leftTerms[j].merged = true;;
			}
		}
	}
	let result = [];
	for(let i = 0; i < leftTerms.length; i++) {
		if(leftTerms[i].merged != true) {
		result.push(leftTerms[i]);
		}
	}
	
	return result;
}



export function trie_degree(terms) {
	for(let j = 0; j < terms.length; j++){
		for(let i = 0; i < terms.length - 1; i++) {
			if(terms[i].degree > terms[i + 1].degree) {
				let temp = terms[i];
				terms[i] = terms[i + 1];
				terms[i + 1] = temp;
			}
		}
	}
	return terms;
}


export function formatOutput(terms) {
	let result = "";

	for(let i = 0; i < terms.length; i++) {
		if(i === 0) {
			result += terms[i].coef + " * X^" + terms[i].degree;
		} else if(terms[i].coef >= 0) {
			result += " + " + terms[i].coef + " * X^" + terms[i].degree;
		} else {
			result += " - " + my_abs(terms[i].coef) + " * X^" + terms[i].degree;
		}
	}
	return result + " = 0";
}
//const terms = reduceEquation("5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0");
// console.log(formatOutput(terms));

// 