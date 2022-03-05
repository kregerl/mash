# Mash

***

## Types

Mash currently supports the following types:

- Numerics
    - Double: Any number with a decimal point.
    - Integer: Any whole number with no decimal point.
    - Hex: A number inputted in the format 0x____  `0xA = 10`
    - Binary: A number inputted in the format 0b____ `0b00000101 = 5`

- Strings: Inputted in by surrounding words with quotation marks "  
  Ex: `x = "testing"`
    - Has few supported operations including:
        - Addition: `"test" + "test" = "testtest"`
        - Subtraction: `"This is a test" - "This" = " is a test"`
        - Multiplication: `"test" * 3 = "testtesttest"`

- Vectors: Inputted using square brackets around a comma seperated list of values or with vector slicing.
  Ex: `x = [1:3] = [1, 2, 3]`
    - Supports most math operations, see **Vector Operations** below

In the future sets will also be added along with much more operations. 
## Math Operators & Built-In Functions

- Addition: <b> x + y </b>
- Subtraction: <b> x - y </b>
- Multiplication: <b> x * y </b>
- Division: <b> x / y </b>
- Modulo: <b> x % y </b>
- Exponents: <b> x**y or exp(x, y) </b>
- Factorial: <b> x! </b>
- Square Root: <b> sqrt(x) </b>
- Sine: <b> sin(x) </b>
- Cosine: <b> cos(x) </b>
- Tangent: <b> tan(x) </b>
- Cotangent: <b> cot(x) </b>
- Secant: <b> sec(x) </b>
- Cosecant: <b> csc(x) </b>
- Arcsin: <b> arcsin(x) </b>
- Arccos: <b> arccos(x) </b>
- Arctan: <b> arctan(x) </b>
- Natural Log: <b> ln(x) </b>
- Log base 10: <b> log(x) </b>
- Log base x: <b> logb(x, y) </b>

[comment]: <> (- Greatest Common Divisor &#40;GCD&#41;: <b> gcd&#40;x, y&#41; </b>)

[comment]: <> (- Least Common Multiple: <b> lcm&#40;x, y&#41; </b>)

[comment]: <> (- Combination &#40;Read x choose y&#41;: <b> choose&#40;x, y&#41; </b>)

[comment]: <> (- [ ] Permutation)

## Bitwise Operators

- Or: <b> x | y or box(x, y) </b>
- And: <b> x & y or band(x, y) </b>
- Xor: <b> x ^ y </b>
- Bitwise shift left <b> x << y </b>
- Bitwise shift right <b> x >> y </b>

## Variables

Variables can be defined by using the equals(`=`) sign.  
Ex: `x = 10 * 2`  
The variable `x` will be assigned the value on the other side of the equal sign, in this case `20`.

The value of a variable can be displayed again simply by typing the variable and pressing enter.  
Ex: `x`  
Will print the value in `x` or `20` if using the previous example.

Variables can be used in operations and other variable assignments.

```shell
Mash > x
20
Mash > y = x + 5
25
Mash > z = [1, 2, x]
[1, 2, 20]
```

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
Mash > z = [1:6]
Mash > z
[1, 2, 3, 4, 5, 6]
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

