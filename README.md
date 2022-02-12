# Mash

***


## Math Operators

- Addition: <b> x + y </b>
- Subtraction: <b> x - y </b>
- Multiplication: <b> x * y </b>
- Division: <b> x / y </b>
- Modulo: <b> x % y or mod(x, y) </b>
- Exponents: <b> x**y or exp(x, y) </b>
- Factorial: <b> x! </b>

[comment]: <> (Not implemented yet)

[comment]: <> (- Square Root: <b> sqrt&#40;x&#41; </b>)

[comment]: <> (- Sine: <b> sin&#40;x&#41; </b>)

[comment]: <> (- Cosine: <b> cos&#40;x&#41; </b>)

[comment]: <> (- Tangent: <b> tan&#40;x&#41; </b>)

[comment]: <> (- Cotangent: <b> cot&#40;x&#41; </b>)

[comment]: <> (- Secant: <b> sec&#40;x&#41; </b>)

[comment]: <> (- Cosecant: <b> csc&#40;x&#41; </b>)

[comment]: <> (- arcsin: <b> arcsin&#40;x&#41; </b>)

[comment]: <> (- arccos: <b> arccos&#40;x&#41; </b>)

[comment]: <> (- arctan: <b> arctan&#40;x&#41; </b>)

[comment]: <> (- Natural Log: <b> ln&#40;x&#41; </b>)

[comment]: <> (- Log base 10: <b> log&#40;x&#41; </b>)

[comment]: <> (- Log base x: <b> logb&#40;x, y&#41; </b>)

[comment]: <> (- Greatest Common Divisor &#40;GCD&#41;: <b> gcd&#40;x, y&#41; </b>)

[comment]: <> (- Least Common Multiple: <b> lcm&#40;x, y&#41; </b>)

[comment]: <> (- Combination &#40;Read x choose y&#41;: <b> choose&#40;x, y&#41; </b>)

[comment]: <> (- [ ] Permutation)

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

