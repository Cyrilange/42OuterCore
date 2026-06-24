_this project is made by csalamit_
# Computor v1

## What is a Polynomial?

A polynomial is an expression made of multiple terms linked together with `+` or `-` operators.

**Examples of terms:** `6y`, `3x²`, `5`

Depending on the number of terms, we use different names:
- 1 term → **monomial**
- 2 terms → **binomial**
- 3 terms → **trinomial**
- 4+ terms → **polynomial** (from the Greek *poly*, meaning "many")

### Example

`3x² + x - 5` can be written more explicitly as `3 * x^2 + 1 * x^1 + (-5) * x^0`

Here `5` is a **constant term** — its value never changes regardless of `x`.

---

## Degree of a Term

The degree of a term is determined by the exponent of its variable part.

- In `5 * x^2`, the degree is `2`
- In `4 * x^1`, the degree is `1`
- In `7 * x^0`, the degree is `0` (constant)

For multi-variable terms like `8y³x²`, the degree is the sum of all exponents: `3 + 2 = 5`.

The **degree of a polynomial** is the highest degree among all its terms.


---

## Reduced Form

When solving, everything is moved to the left side of the equation and terms are arranged from lowest to highest degree:

`5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0` → `4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0`

---
## solve

### degree1
_Linear Polynomials_ 


x = -b / a
        if(terms[i].degree === 1) { a = terms[i].coef; }
        if(terms[i].degree === 0) { b = terms[i].coef; }

### degree2
_Quadratic Polynomials_

formula :

Δ = b² - 4ac

if Δ > 0 :
    x1 = (-b + √Δ) / 2a
    x2 = (-b - √Δ) / 2a

if Δ = 0 :
    x = -b / 2a

if Δ < 0 :
    x1 = -b/2a + i√(-Δ)/2a
    x2 = -b/2a - i√(-Δ)/2a


## Usage

---
in JS you use node so :
### _node polynomial/poly.js_
---
because on my package.json I wrote a sript you can make it work by :


### _npm start_
---


```bash
(node polynomial/poly.js / npm start ) "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
# Or interactively:
node polynomial/poly.js or npm start
Enter equation: 5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0
```

Each term must follow the format: `coefficient * X^degree`

---

## Examples

```bash
$ node polynomial/poly.js "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0" or npm start "5 * X^0 + 4 * X^1 - 9.3 * X^2 = 1 * X^0"
Reduced form: 4 * X^0 + 4 * X^1 - 9.3 * X^2 = 0
Polynomial degree: 2
Discriminant is strictly positive, the two solutions are:
0.905239
-0.475131

$ node polynomial/poly.js "5 * X^0 + 4 * X^1 = 4 * X^0" or npm start "5 * X^0 + 4 * X^1 = 4 * X^0"
Reduced form: 1 * X^0 + 4 * X^1 = 0
Polynomial degree: 1
The solution is: -0.25





```



## Ressources
[polynomial](https://www.mathsisfun.com/algebra/polynomials-solving.html)
[degree1](https://www.mathsisfun.com/algebra/linear-equations.html)
[degree2]()