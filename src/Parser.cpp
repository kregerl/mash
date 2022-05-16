#include "Parser.h"
#include "Nodes.h"
#include <iostream>
#include <map>

Parser::Parser(const std::vector<Token> &tokens) : m_tokens(tokens), m_currentIndex(0) {
    m_currentToken = m_tokens.at(m_currentIndex);
}

void Parser::next() {
    if (m_currentIndex < m_tokens.size() - 1) {
        m_currentToken = m_tokens.at(++m_currentIndex);
    }

}

AbstractNode *Parser::parse() {
    auto statements = std::vector<AbstractNode *>();

    while (m_currentToken.getType() != TokenType::EndOfLine) {
        statements.push_back(statement());
    }

//    auto n = assignment();
//    if (m_currentToken.getType() != TokenType::EndOfLine) {
//        throw EvaluatorException("Expected token EOL but got token '" + m_currentToken.toString() + "'");
//    }
    return new ProgramNode(statements);
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
    } else if (token.getType() == TokenType::DoubleQuote) {
        next();
        std::string str;
        while (m_currentToken.getType() != TokenType::DoubleQuote) {
            if (m_currentToken.getType() == TokenType::EndOfLine) {
                throw EvaluatorException("Expected token \"");
            }
            str += m_currentToken.getValue() + " ";
            next();
        }
        next();
        str = str.substr(0, str.size() - 1);
        AbstractNode *node = new StringNode(StringLiteral(str));
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

AbstractNode *Parser::conditional() {
    AbstractNode *node = additiveExpression();

    while (m_currentToken.getType() == TokenType::LessThan || m_currentToken.getType() == TokenType::GreaterThan) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::LessThan) {
            next();
            node = new BinaryOpNode(BinaryOpType::LessThan, node, additiveExpression());
        }
        if (token.getType() == TokenType::GreaterThan) {
            next();
            node = new BinaryOpNode(BinaryOpType::GreaterThan, node, additiveExpression());
        }
    }
    return node;
}

AbstractNode *Parser::shift() {
    AbstractNode *node = conditional();
    while (m_currentToken.getType() == TokenType::BitwiseShiftLeft ||
           m_currentToken.getType() == TokenType::BitwiseShiftRight) {
        Token token = m_currentToken;
        if (token.getType() == TokenType::BitwiseShiftLeft) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Shift_Left, node, conditional());
        } else if (token.getType() == TokenType::BitwiseShiftRight) {
            next();
            node = new BinaryOpNode(BinaryOpType::BW_Shift_Right, node, conditional());
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

    IdentifierNode *identifier;
    AbstractNode *expression;

    if (m_currentToken.getType() != TokenType::Identifier) {
        throw EvaluatorException("Expected identifier after variable declaration keyword.");
    }
    identifier = new IdentifierNode(m_currentToken.getValue());

    next();
    if (m_currentToken.getType() != TokenType::Equals) {
        throw EvaluatorException("Expected equals after identifier.");
    }
    next();
    expression = bitwiseOr();

    return new AssignmentNode(identifier, expression);
}

AbstractNode *Parser::block() {
    auto statements = std::vector<AbstractNode *>();

    // Consume '{'
    next();

    while (m_currentToken.getType() != TokenType::RBrace && m_currentToken.getType() != TokenType::EndOfLine) {
        statements.push_back(statement());
    }

    if (m_currentToken.getType() != TokenType::RBrace) {
        throw EvaluatorException("Expected enclosing right brace.");
    }

    // Consume '}'
    next();

    return new BlockNode(statements);
}

AbstractNode *Parser::print() {
    // Consume 'print'
    next();

    if (m_currentToken.getType() != TokenType::LParen) {
        throw EvaluatorException("Expected enclosing parenthesis around the contents of print statement.");
    }
    // Consume '('
    next();

    AbstractNode *expression = bitwiseOr();

    if (m_currentToken.getType() != TokenType::RParen) {
        throw EvaluatorException("Expected enclosing parenthesis around the contents of print statement.");
    }
    // Consume ')'
    next();

    return new PrintNode(expression);
}

AbstractNode *Parser::ifStatement() {

    AbstractNode *conditional;
    AbstractNode *ifBlock;


    // Consume "if" token
    next();

    if (m_currentToken.getType() != TokenType::LParen) {
        throw EvaluatorException("Expected enclosing parenthesis around the condition.");
    }
    // Consume '('
    next();

    conditional = bitwiseOr();

    if (m_currentToken.getType() != TokenType::RParen) {
        throw EvaluatorException("Expected enclosing parenthesis around the condition.");
    }
    // Consume ')'
    next();

    ifBlock = block();

    std::map<AbstractNode *, AbstractNode *> elifs;

    while (m_currentToken.getType() == TokenType::kw_elif) {
        // Consume 'elif'
        next();
        AbstractNode *elifConditional = bitwiseOr();

        AbstractNode *elifBlock = block();

        elifs[elifConditional] = elifBlock;
    }

    if (m_currentToken.getType() != TokenType::kw_else) {
        return new ConditionalNode(conditional, ifBlock, elifs);
    }

    // Consume 'else'
    next();

    AbstractNode *elseBlock = block();

    return new ConditionalNode(conditional, ifBlock, elifs, elseBlock);

}

AbstractNode *Parser::functionDefinition() {
    std::string id;
    std::vector<std::string> parameterIdentifiers;
    AbstractNode *functionBlock;

    // Consume 'fn'
    next();

    id = m_currentToken.getValue();

    // Consume function identifier
    next();

    if (m_currentToken.getType() != TokenType::LParen) {
        throw EvaluatorException("Expected left enclosing parenthesis around the function parameters.");
    }

    // Consume '('
    next();

    if (m_currentToken.getType() != TokenType::RParen) {

        parameterIdentifiers.emplace_back(m_currentToken.getValue());

        // Consume first param
        next();

        while (m_currentToken.getType() == TokenType::Comma) {
            // Consume ','
            next();

            parameterIdentifiers.emplace_back(m_currentToken.getValue());

            // Consume param
            next();
        }
    }

    if (m_currentToken.getType() != TokenType::RParen) {
        throw EvaluatorException("Expected right enclosing parenthesis around the function parameters.");
    }

    // Consume ')'
    next();

    functionBlock = block();


    return new FunctionDefinitionNode(id, parameterIdentifiers, functionBlock);
}

AbstractNode *Parser::parseReturn() {
    std::vector<AbstractNode *> expressions;

    // Consume 'return'
    next();


    if (m_currentToken.getType() != TokenType::RBrace) {

        expressions.emplace_back(bitwiseOr());

        while (m_currentToken.getType() == TokenType::Comma) {

            // Consume ','
            next();

            expressions.emplace_back(bitwiseOr());
        }
    }

    return new ReturnNode(expressions);
}


AbstractNode *Parser::statement() {
    switch (m_currentToken.getType()) {
        case TokenType::Identifier:
            return assignment();
        case TokenType::LBrace:
            return block();
        case TokenType::kw_print:
            return print();
        case TokenType::kw_if:
            return ifStatement();
        case TokenType::kw_fn:
            return functionDefinition();
        case TokenType::kw_return:
            return parseReturn();
        default:
            throw EvaluatorException("TODO: Fix later --- Unknown.");
    }
}


