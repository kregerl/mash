#ifndef MASH_LEXER_H
#define MASH_LEXER_H

#include <string>
#include <vector>


const static std::string typeStrings2[] = {"Error", "Number", "Bitwiseand", "Bitwiseor", "Addition", "Subtraction",
                                           "Multiplication",
                                           "Division", "Modulo", "Exp", "Factorial", "LParen",
                                           "RParen", "Equals", "Identifier", "Comma"};

enum class TokenType {
    Error = 0,
    Number,
    Bitwiseand,
    Bitwiseor,
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Modulo,
    Exp,
    Factorial,
    LParen,
    RParen,
    Equals,
    Identifier,
    Comma
};

class Token {
public:
    Token() = default;

    Token(const std::string &value, const TokenType &type);

    ~Token() = default;

    const TokenType &getType();

    const std::string &getValue();

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

    friend bool operator==(const Token &t1, const Token &t2);

private:
    TokenType m_type;
    std::string m_value;
};


class Lexer {
public:
    Lexer(const std::string &expression);

    ~Lexer() = default;

    static Token getTokenFromChar(const char &c);

    Token readIdentifierToken(int *i);

    Token readNumberToken(int *i);

    std::vector<Token> tokenize();

private:
    std::string m_expression;
};


#endif //MASH_LEXER_H
