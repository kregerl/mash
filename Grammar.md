#Grammar
``` 
Function ::= (Identifier '(' Identifier ')' '=')* Assignment
Assignment ::= (Identifier ('-' | '+' | '*' | '/' | '%' | '>>' | '<<' | '&' | '^' | '|')* '=')* Bitwise-OR
Bitwise-OR ::= Bitwise-XOR ('|' Bitwise-XOR)*
Bitwise-XOR ::= Bitwise-AND ('^' Bitwise-AND)*
Bitwise-AND ::= Shift ('&' Shift)*
Shift ::= Additive-Expression (('<<' | '>>') Additive-Expression)*
Additive-Expression ::= Multiplicative-Expression (('+' | '-') Multiplicative-Expression)*
Multiplicative-Expression ::= (Collection | Exponential-Expression) (('*' | '/' | '%') (Collection | Exponential-Expression) )*
Exponential-Expression ::= Factorial-Expression ('**' Factorial-Expression)*
Collection ::= ('-' | '+')* (Vector | Set)
Set ::= ('{' ((Factor | Factor ',')* | Factor '..' Factor) '}') 
Vector ::= ('[' ((Factor | Factor ',')* | Factor '..' Factor) ']')
Factorial-Expression ::= Factor ('!')*
Factor ::= ('+' | '-') Integer | Integer | '(' Bitwise-OR ')'
Identifier ::= #'[A-Za-z0-9]+_*'
Integer ::= #'[0-9]+' '.'? #'[0-9]*'
```
