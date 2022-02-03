#ifndef MASH_PARSER_H
#define MASH_PARSER_H

#include "Lexer.h"
#include "Nodes.h"


// TODO: Refactor Node to contain a list of children. Also make subclasses of Node that can hold errors.
//class Node {
//public:
//    explicit Node(const Token &token);
//
//    explicit Node(const Token &token, Node *left, Node *right);
//
//    ~Node();
//
//    friend std::ostream &operator<<(std::ostream &os, const Node &node);
//
//public:
//    Token token;
//    Node *left;
//    Node *right;
//
//};

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

private:
    const std::vector<Token> m_tokens;
    int m_currentIndex;
    Token m_currentToken;

};


#endif //MASH_PARSER_H
