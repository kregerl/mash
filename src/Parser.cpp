#include "Parser.h"
#include <iostream>

Node::Node(const Token &token) : token(token), left(nullptr), right(nullptr) {}

Node::Node(const Token &token, Node *left, Node *right) : token(token), left(left), right(right) {}

Node::~Node() {
    delete left;
    delete right;
}

std::ostream &operator<<(std::ostream &os, const Node &node) {
    os << "Token: " << node.token;
    if (node.left)
        os << ", " << "Children: " << *node.left;
    if (node.right)
        os << ", " << *node.right;
    return os;
}

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_currentIndex(0) {
    m_currentToken = m_tokens.at(m_currentIndex);
}

void Parser::next() {
    if (m_currentIndex < m_tokens.size() - 1) {
        m_currentToken = m_tokens.at(++m_currentIndex);
    }

}

Node *Parser::parse() {
    return expression();
}

Node *Parser::factor() {
    Token token = m_currentToken;
    if (token.getType() == TokenType::Number) {
        next();
        return new Node(token);
    } else if (token.getType() == TokenType::LParen) {
        // Remove "LParen" from the list
        next();
        Node *node = expression();
        // Remove RParen from the list after parsing the expression inside
        next();
        return node;
    } else if (token.getType() == TokenType::Subtraction) {
        next();
        Node *node = new Node(token, nullptr, factor());
        return node;
    }
    return nullptr;
}

Node *Parser::term() {
    Node *node = factor();

    while (m_currentToken.getType() == TokenType::Multiplication || m_currentToken.getType() == TokenType::Division) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Multiplication) {
            next();
        } else if (token.getType() == TokenType::Division) {
            next();
        }
        node = new Node(token, node, factor());
    }

    return node;
}

Node *Parser::expression() {
    Node *node = term();

    while (m_currentToken.getType() == TokenType::Addition || m_currentToken.getType() == TokenType::Subtraction) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Addition) {
            next();
        } else if (token.getType() == TokenType::Subtraction) {
            next();
        }
        node = new Node(token, node, term());
    }

    return node;
}







