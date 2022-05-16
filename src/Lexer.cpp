#include "Lexer.h"
#include <iostream>
#include <sstream>

// TODO: Change the lexer so it doesn't read all the tokens at once, but as the parser requests them from the lexer.
// TODO: Have a pop, peek(n) -> where peek(n) will peek n tokens ahead as long as it is doesn't reach EOF. The peek function definition: Token peek(int n = 1);
// TODO: Add the rest of the tokens into the TokenType enum and add Tokens for each.

Token::Token(const std::string &value, const TokenType &type) : m_value(value), m_type(type),
                                                                m_internalType(InternalType::Double) {}

Token::Token(const std::string &value, const TokenType &type, const InternalType &iType) :
        m_value(value),
        m_type(type),
        m_internalType(iType) {}

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

std::string Token::toString() const {
    std::string result = "<" + typeStrings2[static_cast<int>(m_type)] + ">: " + m_value;
    return result;
}

InternalType Token::getInternalType() const {
    return m_internalType;
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
        case '[':
            return {str, TokenType::LBracket};
        case ']':
            return {str, TokenType::RBracket};
        case '{':
            return {str, TokenType::LBrace};
        case '}':
            return {str, TokenType::RBrace};
        case ':':
            return {str, TokenType::Colon};
        case '\"':
            return {str, TokenType::DoubleQuote};
        case '<':
            return {str, TokenType::LessThan};
        case '>':
            return {str, TokenType::GreaterThan};
        default:
            return {};
    }
}

Token Lexer::readNumberToken(int *i) {
    int index = *i;
    if (m_expression[index] == '0' &&
        (std::tolower(m_expression[index + 1]) == 'x' || std::tolower(m_expression[index + 1]) == 'b')) {
        char next = std::tolower(m_expression[index + 1]);
        index += 2;
        std::string number;
        while (index < m_expression.length() && std::isalnum(m_expression[index])) {
            number.push_back(m_expression[index++]);
        }
        *i = index - 1;
        if (next == 'x') {
            int n;
            std::stringstream(number) >> std::hex >> n;
            return {std::to_string(n), TokenType::Number, InternalType::Hex};
        } else {
            bool valid = true;
            for (char numChar : number) {
                if (numChar == '0' || numChar == '1') {
                    continue;
                } else {
                    valid = false;
                    break;
                }
            }

            if (valid) {
                int n;
                n = std::stoi(number, nullptr, 2);
                return {std::to_string(n), TokenType::Number, InternalType::Binary};
            } else {
                throw TokenizeException("Binary numbers must be made up of 1's and 0's.");
            }
        }
    } else {
        std::string number;
        while (index < m_expression.length() && std::isdigit(m_expression[index])) {
            number.push_back(m_expression[index++]);
        }
        InternalType type = InternalType::Double;
        std::string decimal;
        if (m_expression[index] == '.') {
            while (index < m_expression.length() && std::isdigit(m_expression[++index])) {
                decimal.push_back(m_expression[index]);
            }
            number.push_back('.');
            number.append(decimal);
        } else {
            type = InternalType::Integer;
        }
        *i = index - 1;
        return {number, TokenType::Number, type};
    }

}

// TODO: Finish this up, new tokenize function thats cleaner and easier to add to.
std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    for (int i = 0; i < m_expression.size(); i++) {
        char c = m_expression[i];
        switch (c) {
            case ' ':
            case '\n':
                continue;
            case '+':
            case '-':
            case '/':
            case '%':
            case '^':
            case '&':
            case '|':
            case '=':
            case '!':
            case '(':
            case ')':
            case ',':
            case '[':
            case ']':
            case '{':
            case '}':
            case ':':
            case '\"':
                tokens.emplace_back(getTokenFromChar(c));
                break;
            case '*':
            case '<':
            case '>':
                if (m_expression[i + 1] == c) {
                    tokens.emplace_back(getTokenFromString(std::string(c, 2)));
                    i++;
                } else {
                    tokens.emplace_back(getTokenFromChar(c));
                }
                break;
            case '.':
                tokens.emplace_back(readNumberToken(&i));
                break;
            default:
                if (std::isalpha(c)) {
                    std::string word = readWord(i);
                    Token token = getTokenFromString(word);

                    tokens.emplace_back(token);
                } else if (std::isdigit(c)) {
                    tokens.emplace_back(readNumberToken(&i));
                }
                break;

        }
    }
    tokens.emplace_back(Token("", TokenType::EndOfLine));

    return tokens;
}

Token Lexer::getTokenFromString(const std::string &string) {
    TokenType type;
    if (string == "**") {
        type = TokenType::Exp;
    } else if (string == "<<") {
        type = TokenType::BitwiseShiftLeft;
    } else if (string == ">>") {
        type = TokenType::BitwiseShiftLeft;
    } else if (string == "var") {
        type = TokenType::kw_var;
    } else if (string == "print") {
        type = TokenType::kw_print;
    } else if (string == "if") {
        type = TokenType::kw_if;
    } else if (string == "else") {
        type = TokenType::kw_else;
    } else if (string == "elif") {
        type = TokenType::kw_elif;
    } else if (string == "fn") {
        type = TokenType::kw_fn;
    } else if (string == "return") {
        type = TokenType::kw_return;
    } else {
        type = TokenType::Identifier;
    }

    return {string, type};
}

std::string Lexer::readWord(int &i) {
    std::string word;
    while (i < m_expression.length() && (std::isalpha(m_expression[i]) || m_expression[i] == '_')) {
        word.push_back(m_expression[i++]);
    }
    i--;
    return word;
}


// TODO: Make the identifiers "strings" instead and when a " is encountered, read until another " is found in order to read the whitespaces.
//std::vector<Token> Lexer::tokenize() {
//    std::vector<Token> tokens;
//    for (int i = 0; i < m_expression.size(); i++) {
//        char c = m_expression[i];
//        if (c == ' ') {
//            continue;
//        } else if (std::isdigit(c) || c == '.') {
//            tokens.emplace_back(readNumberToken(&i));
//        } else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' || c == '^' || c == '&' || c == '|' ||
//                   c == '=' || c == '!' || c == '(' || c == ')' || c == ',' || c == '[' || c == ']' || c == '}' ||
//                   c == '{' || c == ':' ||
//                   c == '\"') {
//            int next = i + 1;
//            if (c == '*' && next < m_expression.size() && m_expression[next] == '*') {
//                tokens.emplace_back(Token("**", TokenType::Exp));
//                i++;
//            } else {
//                tokens.emplace_back(getTokenFromChar(c));
//            }
//        } else if (c == '>') {
//            int next = i + 1;
//            if (next < m_expression.size() && m_expression[next] == '>') {
//                tokens.emplace_back(Token(">>", TokenType::BitwiseShiftRight));
//                i++;
//            }
//        } else if (c == '<') {
//            int next = i + 1;
//            if (next < m_expression.size() && m_expression[next] == '<') {
//                tokens.emplace_back(Token("<<", TokenType::BitwiseShiftLeft));
//                i++;
//            }
//        } else if (std::isalpha(c)) {
//            Token id = readIdentifierToken(&i);
//            if (id.getValue() == "var") {
//                tokens.emplace_back(Token(id.getValue(), TokenType::kw_var));
//            } else if (id.getValue() == "print") {
//                tokens.emplace_back(Token(id.getValue(), TokenType::kw_print));
//            } else {
//                tokens.emplace_back(id);
//            }
//        } else if (c == '\n') {
//            continue;
//        } else {
//            std::cout << "Unknown Token: " << c << std::endl;
//        }
//    }
//    tokens.emplace_back(Token("", TokenType::EndOfLine));
//
//    return tokens;
//}




