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
    auto n = bitwiseOr();
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
        AbstractNode *node = bitwiseOr();
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
    }
//    else if (token.getType() == TokenType::Identifier) {
//        next();
//        AbstractNode *node = new NumberNode(std::stod(token.getValue()));
//        return node;
//    }

    return nullptr;
}

AbstractNode *Parser::factorialExpression() {
    AbstractNode *node = factor();
    while (m_currentToken.getType() == TokenType::Factorial) {
        next();
        node = new UnaryOpNode(UnaryOpType::Factorial, node);
    }
    return node;
}

AbstractNode *Parser::exponentialExpression() {
    AbstractNode *node = factorialExpression();
    while (m_currentToken.getType() == TokenType::Exp) {
        next();
        node = new BinaryOpNode(BinaryOpType::Exp, node, factorialExpression());
    }
    return node;
}

AbstractNode *Parser::multiplicativeExpression() {
    AbstractNode *node = exponentialExpression();

    while (m_currentToken.getType() == TokenType::Multiplication || m_currentToken.getType() == TokenType::Division ||
           m_currentToken.getType() == TokenType::Modulo) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Multiplication) {
            next();
            node = new BinaryOpNode(BinaryOpType::Multiply, node, exponentialExpression());
        } else if (token.getType() == TokenType::Division) {
            next();
            node = new BinaryOpNode(BinaryOpType::Divide, node, exponentialExpression());
        } else if (token.getType() == TokenType::Modulo) {
            next();
            node = new BinaryOpNode(BinaryOpType::Modulo, node, exponentialExpression());
        }
//        else if (token.getType() == TokenType::Equals) {
//            next();
//            node = new BinaryOpNode(BinaryOpType::Equals, node, exponentialExpression());
//        }
    }
    return node;
}

AbstractNode *Parser::additiveExpression() {
    AbstractNode *node = multiplicativeExpression();

    while (m_currentToken.getType() == TokenType::Addition || m_currentToken.getType() == TokenType::Subtraction) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::Addition) {
            next();
            node = new BinaryOpNode(BinaryOpType::Plus, node, multiplicativeExpression());
        } else if (token.getType() == TokenType::Subtraction) {
            next();
            node = new BinaryOpNode(BinaryOpType::Minus, node, multiplicativeExpression());
        }
    }

    return node;
}

AbstractNode *Parser::shift() {
    AbstractNode *node = additiveExpression();
    while (m_currentToken.getType() == TokenType::BitwiseShiftLeft ||
           m_currentToken.getType() == TokenType::BitwiseShiftRight) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::BitwiseShiftLeft) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Shift_Left, node, additiveExpression());
        } else if (token.getType() == TokenType::BitwiseShiftRight) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Shift_Right, node, additiveExpression());
        }
    }
    return node;
}

AbstractNode *Parser::bitwiseAnd() {
    AbstractNode *node = shift();
    while (m_currentToken.getType() == TokenType::Bitwiseand) {
        next();
        node = new BinaryOpNode(BinaryOpType::BW_And, node, shift());
    }
    return node;
}

AbstractNode *Parser::bitwiseXor() {
    AbstractNode *node = bitwiseAnd();
    while (m_currentToken.getType() == TokenType::Bitwisexor) {
        next();
        node = new BinaryOpNode(BinaryOpType::BW_Xor, node, bitwiseAnd());
    }
    return node;
}

AbstractNode *Parser::bitwiseOr() {
    AbstractNode *node = bitwiseXor();
    while (m_currentToken.getType() == TokenType::Bitwiseor) {
        next();
        node = new BinaryOpNode(BinaryOpType::BW_Or, node, bitwiseXor());
    }
    return node;
}



