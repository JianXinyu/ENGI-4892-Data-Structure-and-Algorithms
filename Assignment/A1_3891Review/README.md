Implement polymorphic code for an expression calculator.

In mathematics (as in C++!), an expression is anything that can be evaluated: a literal value, an operation or a value inside of parentheses. In this assignment, you will construct the building blocks of a simple arithmetic expression calculator using:

- polymorphism
- smart pointers and move semantics
- static methods
- string parsing

You will need to implement subclasses of two superclasses, `Expression` and `BinaryExpression`. You will also need to implement a static method of `Expression` that parses a string like `"3 + 4"` and turns it into an expression that can be evaluted. The classes you write will represent:

- literal values (e.g., `7` or `4.2`)
- addition
- subtraction
- multiplication
- division

Start by reading the header file [Expression.h](https://memorialu.gitlab.io/Engineering/ECE/Teaching/data-structures/website/assignment/0/Expression.h). Then, as always, make sure that you understand the problem, choose appropriate representations, design algorithms and then --- only then --- write the code. I would suggest that you follow this process for the `Expression::Literal` method first, then the `BinaryOperation::Add` and other `BinaryOperation` methods one at a time.

