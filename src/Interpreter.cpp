#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter() {}

Interpreter::~Interpreter() {}

Node *Interpreter::visit(Node *ast) {
    if (ast != nullptr) {
        switch (ast->token.getType()) {
            case TokenType::Number:
                return visitNumber(ast);
            case TokenType::Bitwiseand:
                break;
            case TokenType::Bitwiseor:
                break;
            case TokenType::Addition:
                return visitAdd(ast);
            case TokenType::Subtraction:
                return visitSub(ast);
            case TokenType::Multiplication:
                return visitMul(ast);
            case TokenType::Division:
                break;
            case TokenType::Modulus:
                break;
            case TokenType::Exp:
                break;
            case TokenType::Factorial:
                break;
            case TokenType::LParen:
                break;
            case TokenType::RParen:
                break;
            case TokenType::Comma:
                break;
        }
    } else {
        std::cout << "Error" << std::endl;
        return nullptr;
    }
}

Node *Interpreter::visitNumber(Node *node) {
    return node;
}

Node *Interpreter::visitAdd(Node *node) {
    double result = stod(visit(node->left)->token.getValue()) + stod(visit(node->right)->token.getValue());
    return new Node(Token(std::to_string(result), TokenType::Number));
}

Node *Interpreter::visitSub(Node *node) {
    double result = 0;
    if (node->left && node->right) {
        result = stod(visit(node->left)->token.getValue()) - stod(visit(node->right)->token.getValue());
    } else if (node->right) {
        result = -1 * stod(visit(node->right)->token.getValue());
    }
//    double result = stod(visit(node->left)->token.getValue()) - stod(visit(node->right)->token.getValue());
    return new Node(Token(std::to_string(result), TokenType::Number));
}

Node *Interpreter::visitMul(Node *node) {
    double result = stod(visit(node->left)->token.getValue()) * stod(visit(node->right)->token.getValue());
    return new Node(Token(std::to_string(result), TokenType::Number));
}
