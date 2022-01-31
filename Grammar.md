#Grammar
``` 
Function ::= (Identifier '(' Identifier ')' '=')* Assignment
Assignment ::= (Identifier ('-' | '+' | '*' | '/' | '%' | '>>' | '<<' | '&' | '^' | '|')* '=')* Exponential-Expression
Exponential-Expression ::= Bitwise-OR ('**' Bitwise-OR)*
Bitwise-OR ::= Bitwise-XOR ('|' Bitwise-XOR)*
Bitwise-XOR ::= Bitwise-AND ('^' Bitwise-AND)*
Bitwise-AND ::= Shift ('&' Shift)*
Shift ::= Additive-Expression (('<<' | '>>') Additive-Expression)*
Additive-Expression ::= Multiplicative-Expression (('+' | '-') Multiplicative-Expression)*
Multiplicative-Expression ::= (Collection | Factor) (('*' | '/' | '%') (Collection | Factor) )*
Collection ::= ('-' | '+')* (Vector | Set)
Set ::= ('{' ((Factor | Factor ',')* | Factor '..' Factor) '}') 
Vector ::= ('[' ((Factor | Factor ',')* | Factor '..' Factor) ']')
Factor ::= ('+' | '-') Integer | Integer | '(' Exponential-Expression ')'
Identifier ::= #'[A-Za-z0-9]+_*'
Integer ::= #'[0-9]+' '.'? #'[0-9]*'
```
