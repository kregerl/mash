#include "Parser.h"
#include "Nodes.h"

#include <iostream>

//Node::Node(const Token &token) : token(token), left(nullptr), right(nullptr) {}
//
//Node::Node(const Token &token, Node *left, Node *right) : token(token), left(left), right(right) {}
//
//Node::~Node() {
//    delete left;
//    delete right;
//}
//
//std::ostream &operator<<(std::ostream &os, const Node &node) {
//    os << "Token: " << node.token;
//    if (node.left)
//        os << ", " << "Children: " << *node.left;
//    if (node.right)
//        os << ", " << *node.right;
//    return os;
//}

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_currentIndex(0) {
    m_currentToken = m_tokens.at(m_currentIndex);
}

void Parser::next() {
    if (m_currentIndex < m_tokens.size() - 1) {
        m_currentToken = m_tokens.at(++m_currentIndex);
    }

}

// TODO: Assert that the expression is at the end.
Node *Parser::parse() {
    return expression();
}

Node *Parser::factor() {
    Token token = m_currentToken;
    if (token.getType() == TokenType::Number) {
        next();
        return new NumberNode(token);
    } else if (token.getType() == TokenType::LParen) {
        // Remove "LParen" from the list
        next();
        Node *node = expression();
        // Remove RParen from the list after parsing the expression inside
        if (m_currentToken.getType() == TokenType::RParen) {
            next();
        } else {
            node = new NumberNode("Missing closing parenthesis!");
        }
        return node;
    } else if (token.getType() == TokenType::Subtraction) {
        next();
        Node *node = new UnaryOpNode(token, factor());
        return node;
    } else if (token.getType() == TokenType::Identifier) {
        next();
        Node *node = new IdentifierNode(token);
        return node;
    }
    return nullptr;
}

Node *Parser::term() {
    Node *node = factor();

    // Unary, right places operators.
    if (m_currentToken.getType() == TokenType::Factorial) {
        Token token = m_currentToken;
        next();
        node = new UnaryOpNode(token, node);
    }
    while (m_currentToken.getType() == TokenType::Multiplication || m_currentToken.getType() == TokenType::Division ||
           m_currentToken.getType() == TokenType::Modulo || m_currentToken.getType() == TokenType::Equals) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Multiplication) {
            next();
        } else if (token.getType() == TokenType::Division) {
            next();
        } else if (token.getType() == TokenType::Modulo) {
            next();
        } else if (token.getType() == TokenType::Equals) {
            next();
        }
        node = new BinaryOpNode(token, node, factor());
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
        node = new BinaryOpNode(token, node, term());
    }

    return node;
}



