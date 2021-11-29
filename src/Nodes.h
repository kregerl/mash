#ifndef MASH_NODES_H
#define MASH_NODES_H

#include "Lexer.h"
#include <optional>

class NumberNode;

class Node {
public:
    virtual ~Node() = default;

    virtual NumberNode *calculate() = 0;
};


class NumberNode : public Node {
public:
    explicit NumberNode(const Token &token);

    explicit NumberNode(const std::string &str);

    virtual NumberNode *calculate() override;

public:
    Token token;
    std::optional<std::string> errorMessage;
};

class UnaryOpNode : public Node {
public:
    explicit UnaryOpNode(const Token &token, Node *child);

    ~UnaryOpNode() override;

    NumberNode *calculate() override;

public:
    Token token;
    Node *child;
};

class BinaryOpNode : public Node {
public:
    explicit BinaryOpNode(const Token &token, Node *left, Node *right);

    ~BinaryOpNode() override;

    NumberNode *calculate() override;

public:
    Token token;
    Node *left;
    Node *right;
};


#endif //MASH_NODES_H
