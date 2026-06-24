_this project is made by csalamit_

the goal of the project is to learn the boolean algebra with constraint of time and space complexity

# ex00

the first exercice is called adder , the goal is to create an addition with bitwise 

the function is divided into a fews steps:

1 - **find the position** where both are 1 , so we use the & (and).

2- **adds bites without handing the carry** , XOR (^) show 1 only if the bits are differents ( 1 + 1 = 0) ( 1 + 0 = 1 or 0 + 1 = 0)

3- **shift the carry to the left with** << , it is like normal amth , 12 + 9 = 9 + 2 = 1 (carry 1) = 1 + 1 << 1 == 2 << 1 so 21 

# ex01

this exercice is multiplier

The algorithm uses a "shift and add" method, which is how computers multiply numbers at the hardware level.

1. **Check the last bit:** The code looks at the rightmost bit of `b` using `(b & 1)`.
2. **Bitwise Addition:** If that bit is `1`, it adds `a` to the `result`. This addition is done using a nested loop with XOR (`^`) and AND (`&`) gates to handle carries.
3. **Shift:** Then, it shifts `a` to the left (`<<= 1`) to double its value, and shifts `b` to the right (`>>= 1`) to move to the next bit.
4. **Stop:** The loop ends when `b` becomes `0`.

# ex02

### Gray Code Converter

This project implements a **Gray Code** converter. Gray Code is a binary numeral system where two successive values differ in only one bit.



#### What is Gray Code?

In standard binary, counting from `1` to `2` changes two bits at the same time:
* `1` is `01`
* `2` is `10` (both bits flipped!)

In Gray Code, only **one single bit** changes at a time. This is very useful in digital systems, sensors, and error correction because it prevents transitions where multiple bits glitch simultaneously.

---

### 1. Binary to Gray Code
To convert a standard binary number to Gray Code, you shift the binary number to the right by 1 position and perform a bitwise XOR (`^`) with the original number.

* **Formula:** `Gray = Binary ^ (Binary >> 1)`

### 2. Gray Code to Binary
To convert back, you shift and XOR repeatedly until the shifted value becomes zero.

---

# ex03

### Boolean Evaluation - RPN Calculator

This is a simple Rust program that evaluates propositional logic formulas written in **Reverse Polish Notation (RPN)**. 
same as the cpp we did but with bitwise so 1 and 0

The project uses a Stack-based approach to read and calculate logic expressions without needing brackets or parentheses.

#### Supported Operators

| Symbol | Meaning | Mathematical Equivalent | Rust Logic |
| :---: | :--- | :---: | :---: |
| `0` | False | ⊥ | `false` |
| `1` | True | ⊤ | `true` |
| `!` | Negation (NOT) | ¬ | `!a` |
| `&` | Conjunction (AND) | ∧ | `a && b` |
| `\|` | Disjunction (OR) | ∨ | `a \|\| b` |
| `^` | Exclusive OR (XOR) | ⊕ | `a != b` |
| `>` | Implication | ⇒ | `!a \|\| b` |
| `=` | Equivalence | ⇔ | `a == b` |

---

#### How it Works (The Stack Method)

The program reads your formula from left to right:
1. When it sees `0` or `1`, it pushes the value onto a stack.
2. When it sees an operator (like `&`, `|`, `=`), it pops the last two values from the stack, calculates the result, and pushes it back, the result can be either true or false.

Because it uses RPN, **you do not need parentheses** like `(` or `)`. The position of the operator decides the order of calculation.

---











# Ressources 

[rust](https://web.mit.edu/rust-lang_v1.25/arch/amd64_ubuntu1404/share/doc/rust/html/book/first-edition/README.html)