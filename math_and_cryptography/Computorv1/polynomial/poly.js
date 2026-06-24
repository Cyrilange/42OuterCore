import { reduceEquation, formatOutput } from "../Utils/utils.parsing.js";
import { getDegree, degree1, degree2 } from "../Utils/utils_calcul.js";


export function getInput(callback) {
    const input = process.argv[2];
    if(!input) {
        process.stdout.write("Enter equation: ");
        process.stdin.setEncoding("utf8");
        process.stdin.once("data", (data) => {
            callback(data.trim().replace(/"/g, ""));
        });
    } else {
        callback(input);
    }
}

export function solve(equation) {
	
    const terms = reduceEquation(equation);
    process.stdout.write("Reduced form: ");
    console.log(formatOutput(terms));
    if(getDegree(terms) > 0) {process.stdout.write(`Polynomial degree: ${getDegree(terms)}\n`);}
	const degree = getDegree(terms);
	if(degree > 2) {
		console.log("The polynomial degree is strictly greater than 2, I can't solve.");
	} else if(degree == 0) {
		if(terms[0].coef == 0) {
			console.log("Any real number is a solution.");
		} else {
			console.log("No solution.");
		}
	} else if(degree == 1){
		process.stdout.write("The solution is:\n")
		console.log(degree1(terms).toFixed(6));
	} else if(degree == 2) {
		degree2(terms);
	}
	process.exit(0);
}

getInput(solve);



