#include "Lexer.h"
#include <iostream>

// TODO: Change the lexer so it doesn't read all the tokens at once, but as the parser requests them from the lexer.
// TODO: Have a pop, peek(n) -> where peek(n) will peek n tokens ahead as long as it is doesn't reach EOF. The peek function definition: Token peek(int n = 1);
// TODO: Add the rest of the tokens into the TokenType enum and add Tokens for each.

Token::Token(const std::string &value, const TokenType &type) : m_value(value), m_type(type) {}

const TokenType &Token::getType() {
    return m_type;
}

const TokenType &Token::getType() const {
    return m_type;
}

const std::string &Token::getValue() {
    return m_value;
}

const std::string &Token::getValue() const {
    return m_value;
}

std::ostream &operator<<(std::ostream &os, const Token &token) {
    std::string sep = ": ";
    os << "<" << typeStrings2[static_cast<int>(token.m_type)] << ">" << sep << token.m_value;
    return os;
}

bool operator==(const Token &t1, const Token &t2) {
    return t1.m_type == t2.m_type && t1.m_value == t2.m_value;
}

Lexer::Lexer(const std::string &expression) : m_expression(expression) {}

Token Lexer::getTokenFromChar(const char &c) {
    std::string str = std::string(1, c);
    switch (c) {
        case '+':
            return {str, TokenType::Addition};
        case '-':
            return {str, TokenType::Subtraction};
        case '*':
            return {str, TokenType::Multiplication};
        case '/':
            return {str, TokenType::Division};
        case '(':
            return {str, TokenType::LParen};
        case ')':
            return {str, TokenType::RParen};
        case '%':
            return {str, TokenType::Modulo};
        case '^':
            return {str, TokenType::Bitwisexor};
        case '&':
            return {str, TokenType::Bitwiseand};
        case '|':
            return {str, TokenType::Bitwiseor};
        case '!':
            return {str, TokenType::Factorial};
        case '=':
            return {str, TokenType::Equals};
        case ',':
            return {str, TokenType::Comma};
        default:
            return {};
    }
}

Token Lexer::readIdentifierToken(int *i) {
    int index = *i;
    std::string var;
    while (index < m_expression.length() && std::isalpha((m_expression[index]))) {
        var.push_back(m_expression[index++]);
    }
    *i = index - 1;
    return {var, TokenType::Identifier};
}

Token Lexer::readNumberToken(int *i) {
    int index = *i;
    std::string number;
    while (index < m_expression.length() && std::isdigit(m_expression[index])) {
        number.push_back(m_expression[index++]);
    }
    std::string decimal;
    if (m_expression[index] == '.') {
        while (index < m_expression.length() && std::isdigit(m_expression[++index])) {
            decimal.push_back(m_expression[index]);
        }
        number.push_back('.');
        number.append(decimal);
    }
    *i = index - 1;
    return {number, TokenType::Number};
}


std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    for (int i = 0; i < m_expression.size(); i++) {
        char c = m_expression[i];
        if (c == ' ') {
            continue;
        } else if (std::isdigit(c) || c == '.') {
            tokens.emplace_back(readNumberToken(&i));
        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '&' || c == '|' ||
                   c == '=' || c == '!' || c == '(' || c == ')' || c == ',') {
            int next = i + 1;
            if (c == '*' && next < m_expression.size() && m_expression[next] == '*') {
                tokens.emplace_back(Token("**", TokenType::Exp));
                i++;
            } else {
                tokens.emplace_back(getTokenFromChar(c));
            }
        } else if (c == '>') {
            int next = i + 1;
            if (next < m_expression.size() && m_expression[next] == '>') {
                tokens.emplace_back(Token(">>", TokenType::BitwiseShiftRight));
                i++;
            }
        } else if (std::isalpha(c)) {
            tokens.emplace_back(readIdentifierToken(&i));
        } else {
            std::cout << "Unknown Token: " << c << std::endl;
        }
    }
    tokens.emplace_back(Token("", TokenType::EndOfLine));

    return tokens;
}




