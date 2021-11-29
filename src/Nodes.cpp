#include "Nodes.h"
#include <sstream>

NumberNode::NumberNode(const Token &token) : token(token) {}

NumberNode *NumberNode::calculate() {
    return this;
}

NumberNode::NumberNode(const std::string &str) : errorMessage(str) {}


UnaryOpNode::UnaryOpNode(const Token &token, Node *child) : token(token), child(child) {}

NumberNode *UnaryOpNode::calculate() {
    NumberNode *childResult = child->calculate();
    if (childResult->errorMessage) {
        return childResult;
    }
    switch (token.getType()) {
        case TokenType::Subtraction: {
            double result = std::stod(childResult->token.getValue()) * -1.0;
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        default: {
            std::stringstream stream;
            stream << "Unknown Unary Operator type: " << token;
            return new NumberNode(stream.str());
        }
    }
}

UnaryOpNode::~UnaryOpNode() {
    delete child;
}

BinaryOpNode::BinaryOpNode(const Token &token, Node *left, Node *right) : token(token), left(left), right(right) {}

NumberNode *BinaryOpNode::calculate() {
    NumberNode *leftResult = left->calculate();
    NumberNode *rightResult = right->calculate();
    if (leftResult->errorMessage) {
        return leftResult;
    } else if (rightResult->errorMessage) {
        return rightResult;
    }
    switch (token.getType()) {
        case TokenType::Addition: {
            double result = std::stod(leftResult->token.getValue()) + std::stod(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Subtraction: {
            double result = std::stod(leftResult->token.getValue()) - std::stod(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
    }

    return new NumberNode(Token());
}

BinaryOpNode::~BinaryOpNode() {
    delete left;
    delete right;
}

