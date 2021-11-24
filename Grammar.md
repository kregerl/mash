
``` 
binary-op ::= '&' | '|' | '^'
binary-expression ::= expression ( binary-op expression)*
expression ::= additive-expression
additive-expression ::= multiplicative-expression (('+'|'-') multiplicative-expression)*
multiplicative-expression ::= primary (('*'|'/') primary)*
exponent-expression ::= primary '**' exponent-expression | primary  
primary ::= '(' expression ')' | INTEGER | '-' primary


```
