#ifndef MASH_NODES_H
#define MASH_NODES_H

#include "Lexer.h"
#include <optional>
#include <unordered_map>


class NumberNode;

class Node {
public:
    virtual ~Node() = default;

    virtual NumberNode *calculate(std::unordered_map<std::string, Node *> &variables) = 0;
};

//TODO: Make a ValueNode(No token) that NumberNode(holds a token), LiteralNode("holds a token") and ErrorLiteralNode(No token) can inherit from. Operators still inherit from Node
class NumberNode : public Node {
public:
    explicit NumberNode(const Token &token);

    explicit NumberNode(const std::string &str);

    NumberNode *calculate(std::unordered_map<std::string, Node *> &variables) override;

    friend std::ostream &operator<<(std::ostream &os, const NumberNode &node);

public:
    Token token;
    std::optional<std::string> errorMessage;
};

class IdentifierNode : public NumberNode {
public:
    explicit IdentifierNode(const Token &token);

    ~IdentifierNode() override;

    NumberNode *calculate(std::unordered_map<std::string, Node *> &variables) override;
};

class UnaryOpNode : public Node {
public:
    explicit UnaryOpNode(const Token &token, Node *child);

    ~UnaryOpNode() override;

    NumberNode *calculate(std::unordered_map<std::string, Node *> &variables) override;

public:
    Token token;
    Node *child;
};

class BinaryOpNode : public Node {
public:
    explicit BinaryOpNode(const Token &token, Node *left, Node *right);

    ~BinaryOpNode() override;

    NumberNode *calculate(std::unordered_map<std::string, Node *> &variables) override;

public:
    Token token;
    Node *left;
    Node *right;
};

#endif //MASH_NODES_H
