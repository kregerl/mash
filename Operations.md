# Mash

***

## Operators

### Math Operators

- [X] Addition: <b> x + y </b>
- [X] Subtraction: <b> x - y </b>
- [X] Multiplication: <b> x * y </b>
- [X] Division: <b> x / y </b>
- [X] Modulus: <b> x % y or mod(x, y) </b>
- [X] Exponents: <b> x^y or exp(x, y) </b>
- [X] Factorial: <b> x! </b>
- [X] Square Root: <b> sqrt(x) </b>
- [X] Sine: <b> sin(x) </b>
- [X] Cosine: <b> cos(x) </b>
- [X] Combination (Read x choose y): <b> choose(x, y) </b>
- [ ] Permutation

### Bitwise Operators

- [X] Or: <b> x | y or box(x, y) </b>
- [X] And: <b> x & y or band(x, y) </b>
- [X] Xor: <b> bxor(x, y) </b>

## Variables

Variables can be defined by using the equals(`=`) sign.  
Ex: `x = 10 * 2`  
The variable `x` will be assigned the value on the other side of the equal sign, in this case `20`.

The value of a variable can be displayed again simply by typing the variable and pressing enter.  
Ex: `x`  
Will print the value in `x` or `20` if using the previous example.

Variables can be used in operations and other variable assignments.  
Ex: `x * 5`  
Ex: `y = x + 5`  
The example above will assign `y` the value contained in `x` + 5. Following the previous examples, `y` would be 25.

## Functions

Functions can be defined in the following way:  
`<name>(<param 1>, <param 2>, ...) = <param 1> + <param 2> ...`  
Ex: `f(x) = x + 1`  
The function above will accept any value, `x` and return the result of `x + 1`.  
Functions can be defined with as many parameters as the user would like, as long as they all have unique names and are
used after the function declaration.  
Ex: `f(x, y) = x + 1`  
The above function is not valid since it does not use its other parameter.  

Functions can be used alongside operators:  
Ex:  
> `f(x) = x + 1`  
> `f(1) + 3`  
> `5`

