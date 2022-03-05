#ifndef MASH_PARSER_H
#define MASH_PARSER_H

#include "Lexer.h"
#include "Nodes.h"

class Parser {
public:
    explicit Parser(const std::vector<Token> &tokens);

    ~Parser() = default;

    void next();

    AbstractNode *parse();

    AbstractNode *factor();

    AbstractNode *factorialExpression();

    AbstractNode *exponentialExpression();

    AbstractNode *multiplicativeExpression();

    AbstractNode *additiveExpression();

    AbstractNode *shift();

    AbstractNode *bitwiseAnd();

    AbstractNode *bitwiseXor();

    AbstractNode *bitwiseOr();

    AbstractNode *assignment();

private:
    const std::vector<Token> m_tokens;
    int m_currentIndex;
    Token m_currentToken;

};


#endif //MASH_PARSER_H
