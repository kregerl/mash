#include "Nodes.h"
#include <sstream>
#include <cmath>
#include <iostream>

NumberNode::NumberNode(const Token &token) : token(token) {}

NumberNode *NumberNode::calculate(std::unordered_map<std::string, NumberNode *> &variables) {
    switch (token.getType()) {
        case TokenType::Identifier: {
            if (variables.find(token.getValue()) != variables.end()) {
                return variables.at(token.getValue());
            }
        }
        case TokenType::Number: {
            return this;
        }
        default: {
            std::stringstream stream;
            stream << "Unknown number: " << token;
            return new NumberNode(stream.str());
        }
    }

}

NumberNode::NumberNode(const std::string &str) : token(Token("Error:", TokenType::Error)), errorMessage(str) {}


std::ostream &operator<<(std::ostream &os, const NumberNode &node) {
    if (node.errorMessage) {
        os << node.errorMessage.value();
    } else {
        os << node.token;
    }
    return os;
}

UnaryOpNode::UnaryOpNode(const Token &token, Node *child) : token(token), child(child) {}

NumberNode *UnaryOpNode::calculate(std::unordered_map<std::string, NumberNode *> &variables) {
    NumberNode *childResult = child->calculate(variables);
    if (childResult->errorMessage) {
        return childResult;
    }
    switch (token.getType()) {
        case TokenType::Subtraction: {
            double result = std::stod(childResult->token.getValue()) * -1.0;
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Factorial: {
            double result = std::tgamma(1.0 + (stod(childResult->token.getValue())));
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

NumberNode *BinaryOpNode::calculate(std::unordered_map<std::string, NumberNode *> &variables) {
    NumberNode *leftResult = left->calculate(variables);
    NumberNode *rightResult = right->calculate(variables);
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
        case TokenType::Multiplication: {
            double result = std::stod(leftResult->token.getValue()) * std::stod(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Division: {
            if (std::stod(rightResult->token.getValue()) == 0) {
                return new NumberNode("Division by zero!");
            }
            double result = std::stod(leftResult->token.getValue()) / std::stod(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Modulo: {
            // TODO: Check if Modulo works on negative numbers.
            if (std::stod(rightResult->token.getValue()) == 0) {
                return new NumberNode("Modulo by zero!");
            }
            double result = fmod(std::stod(leftResult->token.getValue()), std::stod(rightResult->token.getValue()));
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Bitwiseand: {
            double result = std::stoi(leftResult->token.getValue()) & std::stoi(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Bitwiseor: {
            double result = std::stoi(leftResult->token.getValue()) | std::stoi(rightResult->token.getValue());
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Exp: {
            double result = std::pow(std::stod(leftResult->token.getValue()), std::stod(rightResult->token.getValue()));
            return new NumberNode(Token(std::to_string(result), TokenType::Number));
        }
        case TokenType::Equals: {
            if (leftResult->token.getType() == TokenType::Identifier) {
                variables.insert({leftResult->token.getValue(), rightResult});
                std::stringstream ss;
                ss << leftResult->token.getValue();
                ss << " = ";
                ss << rightResult->token.getValue();
                return new NumberNode(Token(ss.str(), TokenType::Identifier));
            } else {
                return new NumberNode("Cant assign numerics to different values.");
            }
        }
        default: {
            std::stringstream stream;
            stream << "Unknown Binary Operator type: " << token;
            return new NumberNode(stream.str());
        }
    }
}

BinaryOpNode::~BinaryOpNode() {
    delete left;
    delete right;
}


