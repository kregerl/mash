# Mash

***


## Math Operators

- Addition: <b> x + y </b>
- Subtraction: <b> x - y </b>
- Multiplication: <b> x * y </b>
- Division: <b> x / y </b>
- Modulo: <b> x % y or mod(x, y) </b>
- Exponents: <b> x^y or exp(x, y) </b>
- Factorial: <b> x! </b>
- Square Root: <b> sqrt(x) </b>
- Sine: <b> sin(x) </b>
- Cosine: <b> cos(x) </b>
- Tangent: <b> tan(x) </b>
- Cotangent: <b> cot(x) </b>
- Secant: <b> sec(x) </b>
- Cosecant: <b> csc(x) </b>
- arcsin: <b> arcsin(x) </b>
- arccos: <b> arccos(x) </b>
- arctan: <b> arctan(x) </b>
- Natural Log: <b> ln(x) </b>
- Log base 10: <b> log(x) </b>
- Log base x: <b> logb(x, y) </b>
- Greatest Common Divisor (GCD): <b> gcd(x, y) </b>
- Least Common Multiple: <b> lcm(x, y) </b>
- Combination (Read x choose y): <b> choose(x, y) </b>
- [ ] Permutation

## Bitwise Operators

- Or: <b> x | y or box(x, y) </b>
- And: <b> x & y or band(x, y) </b>
- Xor: <b> bxor(x, y) </b>

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

## Vectors and Sets
Vectors and sets are defined in a similar way, using outer braces and comma seperated values.  
A vector is defined by using square brackets, while sets use curley braces.  
Vector Ex: 
```shell
Mash > x = [1, 2, 3]
Mash > x
[1, 2, 3]
Mash > y = [2, 2, 2]
Mash > dot(x, y)
12
```
Set Ex: 
```shell
Mash > x = {1, 3, 5}
Mash > x
{1, 3, 5}
Mash > y = {3, 4, 5}
Mash > union(x, y)
{1, 3, 4, 5}
```

