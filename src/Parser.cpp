#include "Parser.h"
#include "Nodes.h"
#include <iostream>

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_currentIndex(0) {
    m_currentToken = m_tokens.at(m_currentIndex);
}

void Parser::next() {
    if (m_currentIndex < m_tokens.size() - 1) {
        m_currentToken = m_tokens.at(++m_currentIndex);
    }

}

AbstractNode *Parser::parse() {
    auto n = assignment();
    if (m_currentToken.getType() != TokenType::EndOfLine) {
        throw EvaluatorException("Expected token EOL but got token '" + m_currentToken.toString() + "'");
    }
    return n;
}

AbstractNode *Parser::factor() {
    Token token = m_currentToken;
    if (token.getType() == TokenType::Number) {
        next();
        return new NumberNode(NumericLiteral(std::stod(token.getValue()), token.getInternalType()));
    } else if (token.getType() == TokenType::LParen) {
        // Remove "LParen" from the list
        next();
        // The expression used here needs to be updated whenever an operator with lower precedence is added
        AbstractNode *node = bitwiseOr();
        // Remove RParen from the list after parsing the expression inside
        if (m_currentToken.getType() == TokenType::RParen) {
            next();
        } else {
            throw EvaluatorException("Expected token '(' but got '" + m_currentToken.toString() + "'");
        }
        return node;
    } else if (token.getType() == TokenType::Subtraction) {
        next();
        AbstractNode *node = new UnaryOpNode(UnaryOpType::Negation, factor());
        return node;
    } else if (token.getType() == TokenType::Identifier) {
        next();
        AbstractNode *node = new IdentifierNode(token.getValue());
        if (m_currentToken.getType() == TokenType::LParen) {
            next();
            std::vector<AbstractNode *> parameters;
            parameters.emplace_back(bitwiseOr());
            while (m_currentToken.getType() != TokenType::RParen) {
                if (m_currentToken.getType() == TokenType::Comma) {
                    next();
                    parameters.emplace_back(bitwiseOr());
                } else {
                    throw EvaluatorException("Expected token '(' but got '" + m_currentToken.toString() + "'");
                }
            }
            next();
            auto *n = dynamic_cast<IdentifierNode *>(node);
            if (n != nullptr) {
                node = new FunctionNode(n, parameters);
            } else {
                throw EvaluatorException("You can only have identifiers as function parameters");
            }
        }
        return node;
    } else if (token.getType() == TokenType::LBracket) {
        next();
        std::vector<AbstractNode *> contents;
        contents.emplace_back(bitwiseOr());
        while (m_currentToken.getType() != TokenType::RBracket) {
            if (m_currentToken.getType() == TokenType::Comma) {
                next();
                contents.emplace_back(bitwiseOr());
            } else if (m_currentToken.getType() == TokenType::Colon) {
                next();
                int index = contents.size() - 1;
                AbstractNode *first = contents.at(index);
                if (first == nullptr) {
                    first = new NumberNode(NumericLiteral(0, InternalType::Integer));
                }
                AbstractNode *n = new BinaryOpNode(BinaryOpType::VectorSlice, first, bitwiseOr());
                next();
                return n;
            } else {
                throw EvaluatorException("Expected token '[' but got '" + m_currentToken.toString() + "'");
            }
        }
        next();
        return new VectorNode(contents);
    }


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

AbstractNode *Parser::assignment() {
    AbstractNode *node = bitwiseOr();
    while (m_currentToken.getType() == TokenType::Equals) {
        next();
        auto *n = dynamic_cast<IdentifierNode *>(node);
        if (n != nullptr) {
            node = new AssignmentNode(n, bitwiseOr());
        } else {
            auto *fn = dynamic_cast<FunctionNode *>(node);
            if (fn != nullptr) {
                node = new FunctionAssignmentNode(fn, bitwiseOr());
            } else {
                throw EvaluatorException("Assignments must be between an Identifier and a number!");
            }
        }
    }
    return node;
}




