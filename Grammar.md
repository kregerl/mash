#Grammar
``` 
factorial ::= expression '!'
expression ::= binary-expression
binary-op ::= '&' | '|' | '^'
binary-expression ::= additive-expression ( binary-op additive-expression)*
additive-expression ::= multiplicative-expression (('+'|'-') multiplicative-expression)*
multiplicative-expression ::= primary (('*'|'/'|'%') primary)*
exponent-expression ::= primary '^' exponent-expression | primary  
primary ::= '(' expression ')' | INTEGER | ('-' | '+') primary
```
