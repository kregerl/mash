#include "Parser.h"
#include "Nodes.h"

#include <iostream>
#include <cassert>

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
AbstractNode *Parser::parse() {
    auto n = bitwiseExpression();
    assert(("Remaining token is not EOF!", m_currentToken.getType() == TokenType::EndOfLine));
    return n;
}

AbstractNode *Parser::factor() {
    Token token = m_currentToken;
    if (token.getType() == TokenType::Number) {
        next();
        return new NumberNode(std::stod(token.getValue()));
    } else if (token.getType() == TokenType::LParen) {
        // Remove "LParen" from the list
        next();
        // The expression used here needs to be updated whenever an operator with lower precedence is added
        AbstractNode *node = bitwiseExpression();
        // Remove RParen from the list after parsing the expression inside
        if (m_currentToken.getType() == TokenType::RParen) {
            next();
        } else {
//            node = new NumberNode("Missing closing parenthesis!");
        }
        return node;
    } else if (token.getType() == TokenType::Subtraction) {
        next();
        AbstractNode *node = new UnaryOpNode(UnaryOpType::Negation, factor());
        return node;
    } else if (token.getType() == TokenType::Identifier) {
        next();
        AbstractNode *node = new NumberNode(std::stod(token.getValue()));
        return node;
    }
    return nullptr;
}

AbstractNode *Parser::exponent() {
    AbstractNode *node = factor();
    if (m_currentToken.getType() == TokenType::Exp) {
        next();
        node = new BinaryOpNode(BinaryOpType::Exp, node, bitwiseExpression());
    }
    return node;
}

AbstractNode *Parser::term() {
    AbstractNode *node = exponent();

    // Unary, right placed operators.
    if (m_currentToken.getType() == TokenType::Factorial) {
        Token token = m_currentToken;
        next();
        node = new UnaryOpNode(UnaryOpType::Factorial, node);
    }
    while (m_currentToken.getType() == TokenType::Multiplication || m_currentToken.getType() == TokenType::Division ||
           m_currentToken.getType() == TokenType::Modulo || m_currentToken.getType() == TokenType::Equals) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Multiplication) {
            next();
            node = new BinaryOpNode(BinaryOpType::Multiply, node, exponent());
        } else if (token.getType() == TokenType::Division) {
            next();
            node = new BinaryOpNode(BinaryOpType::Divide, node, exponent());
        } else if (token.getType() == TokenType::Modulo) {
            next();
            node = new BinaryOpNode(BinaryOpType::Modulo, node, exponent());
        } else if (token.getType() == TokenType::Equals) {
            next();
            node = new BinaryOpNode(BinaryOpType::Equals, node, exponent());
        }

    }
    return node;
}

AbstractNode *Parser::expression() {
    AbstractNode *node = term();

    while (m_currentToken.getType() == TokenType::Addition || m_currentToken.getType() == TokenType::Subtraction) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Addition) {
            next();
            node = new BinaryOpNode(BinaryOpType::Plus, node, term());
        } else if (token.getType() == TokenType::Subtraction) {
            next();
            node = new BinaryOpNode(BinaryOpType::Minus, node, term());
        }
    }

    return node;
}

AbstractNode *Parser::bitwiseExpression() {
    AbstractNode *node = expression();

    while (m_currentToken.getType() == TokenType::Bitwiseand || m_currentToken.getType() == TokenType::Bitwiseor ||
           m_currentToken.getType() == TokenType::Bitwisexor) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Bitwiseand) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_And, node, bitwiseExpression());
        } else if (token.getType() == TokenType::Bitwiseor) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Or, node, bitwiseExpression());
        } else if (token.getType() == TokenType::Bitwisexor) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Xor, node, bitwiseExpression());
        }
    }

    return node;
}



