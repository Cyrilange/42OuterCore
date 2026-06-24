import { reduceEquation, formatOutput } from "./Utils/utils.parsing.js";
import { getDegree, degree1, degree2 } from "./Utils/utils_calcul.js";

let passed = 0;
let failed = 0;

//make solve not die
function solve(equation) {
	const output = [];
	const originalLog = console.log;
	const originalWrite = process.stdout.write.bind(process.stdout);
	
	console.log = (...args) => output.push(args.join(" "));
	process.stdout.write = (str) => { output.push(str.replace(/\n$/, "")); return true; };

	try {
		const terms = reduceEquation(equation);
		process.stdout.write("Reduced form: ");
		console.log(formatOutput(terms));
		const degree = getDegree(terms);
		if (degree > 0) process.stdout.write(`Polynomial degree: ${degree}\n`);
		if (degree > 2) {
			console.log("The polynomial degree is strictly greater than 2, I can't solve.");
		} else if (degree === 0) {
			if (terms[0].coef === 0) {
				console.log("Any real number is a solution.");
			} else {
				console.log("No solution.");
			}
		} else if (degree === 1) {
			process.stdout.write("The solution is:\n");
			console.log(degree1(terms).toFixed(6));
		} else if (degree === 2) {
			degree2(terms);
		}
	} catch(e) {
		output.push("ERROR: " + e.message);
	}

	console.log = originalLog;
	process.stdout.write = originalWrite;
	return output.join("\n");
}

function test(name, input, checks) {
	const full = solve(input);
	let ok = true;
	for (const check of checks) {
		if (!full.includes(check)) ok = false;
	}
	if (ok) {
		console.log("✅ PASS —", name);
		passed++;
	} else {
		console.log("❌ FAIL —", name);
		console.log("   Output:", full);
		console.log("   Expected to contain:", checks);
		failed++;
	}
}

process.stdout.write('\x1Bc');
console.log("═══════════════════════════════════════════════");
console.log("         COMPUTORV1 — FULL EVAL TESTS          ");
console.log("═══════════════════════════════════════════════\n");

// --- DEGREE 0 ---
console.log("── Degree 0 ──────────────────────────────────");
test("Infinite solutions (5*X^0 = 5*X^0)", "5 * X^0 = 5 * X^0", ["Any", "real"]);
test("No solution (4*X^0 = 8*X^0)", "4 * X^0 = 8 * X^0", ["No solution"]);

// --- DEGREE 1 ---
console.log("\n── Degree 1 ──────────────────────────────────");
test("Basic (5*X^0 = 4*X^0 + 7*X^1)", "5 * X^0 = 4 * X^0 + 7 * X^1", ["0.142857"]);
test("Negative coefficient", "2 * X^0 + 4 * X^1 = 0 * X^0", ["-0.5"]);
test("Zero constant term", "0 * X^0 + 3 * X^1 = 9 * X^0", ["3"]);

// --- DEGREE 2 — POSITIVE DISCRIMINANT ---
console.log("\n── Degree 2 — positive discriminant ─────────");
test("Subject example", "5 * X^0 + 13 * X^1 + 3 * X^2 = 1 * X^0 + 1 * X^1", ["strictly positive", "-0.367", "-3.632"]);
test("Classic poly.js example", "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0", ["strictly positive", "0.905", "-0.475"]);
test("Negative constant", "1 * X^0 - 5 * X^1 + 6 * X^2 = 0 * X^0", ["strictly positive", "0.5", "0.333"]);

// --- DEGREE 2 — ZERO DISCRIMINANT ---
console.log("\n── Degree 2 — zero discriminant ─────────────");
test("Subject example", "6 * X^0 + 11 * X^1 + 5 * X^2 = 1 * X^0 + 1 * X^1", ["-1"]);
test("Perfect square", "1 * X^0 + 2 * X^1 + 1 * X^2 = 0 * X^0", ["-1"]);

// --- DEGREE 2 — NEGATIVE DISCRIMINANT ---
console.log("\n── Degree 2 — negative discriminant ─────────");
test("Subject example", "5 * X^0 + 3 * X^1 + 3 * X^2 = 1 * X^0 + 0 * X^1", ["strictly negative", "-0.5", "1.0408", "* i"]);
test("Another case", "5 * X^0 + 1 * X^1 + 1 * X^2 = 0 * X^0", ["strictly negative", "-0.5", "* i"]);

// --- DEGREE 3+ ---
console.log("\n── Degree 3+ ─────────────────────────────────");
test("Degree 3 — refuse to solve", "1 * X^0 + 1 * X^1 + 1 * X^2 + 1 * X^3 = 0 * X^0", ["degree", "3"]);
test("Degree 4 — refuse to solve", "1 * X^4 = 0 * X^0", ["degree"]);

// --- EDGE CASES ---
console.log("\n── Edge cases ────────────────────────────────");
test("Negative coefficient", "-1 * X^0 + 2 * X^1 = 0 * X^0", ["0.5"]);
test("Decimal coefficient", "5.5 * X^0 = 3.5 * X^0 + 1 * X^1", ["2"]);
test("Zero X^2 term (reduces to degree 1)", "0 * X^2 + 3 * X^1 + 6 * X^0 = 0 * X^0", ["-2"]);

// --- SUMMARY ---
console.log("\n═══════════════════════════════════════════════");
console.log(`  RESULTS: ${passed} passed, ${failed} failed / ${passed + failed} total`);
console.log("═══════════════════════════════════════════════");