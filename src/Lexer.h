#ifndef MASH_LEXER_H
#define MASH_LEXER_H

#include <string>
#include <vector>


const static std::string typeStrings2[] = {"Error", "Number", "Bitwiseand", "Bitwiseor", "Bitwisexor",
                                           "BitwiseShiftLeft", "BitwiseShiftRight", "Addition",
                                           "Subtraction",
                                           "Multiplication",
                                           "Division", "Modulo", "Exp", "Factorial", "LParen",
                                           "RParen", "LBracket", "RBracket", "LBrace", "RBrace", "Equals", "Identifier",
                                           "Comma", "Colon", "End of Line"};


enum class TokenType {
    Error = 0,
    Number,
    Bitwiseand,
    Bitwiseor,
    Bitwisexor,
    BitwiseShiftLeft,
    BitwiseShiftRight,
    Addition,
    Subtraction,
    Multiplication,
    Division,
    Modulo,
    Exp,
    Factorial,
    LParen,
    RParen,
    LBracket,
    RBracket,
    LBrace,
    RBrace,
    DoubleQuote,
    Equals,
    Identifier,
    Comma,
    Colon,
    EndOfLine
};

/*
 * The order of the internal types matter here, they are used to determine the next type for a value.
 * The minimum value is always chosen, so if there is an operation between a double and int the result will be a double
 * since double(0) < integer(1).
 */
enum class InternalType {
    Double = 0, Integer, Hex, Binary
};

const static std::string internalTypeStrings[] = {"Double", "Integer", "Hex", "Binary"};

static std::string internalTypeToString(InternalType type) {
    return internalTypeStrings[static_cast<int>(type)];
}

class Token {
public:
    Token() = default;

    Token(const std::string &value, const TokenType &type);

    Token(const std::string &value, const TokenType &type, const InternalType &internalType);

    ~Token() = default;

    const TokenType &getType();

    const TokenType &getType() const;

    const std::string &getValue();

    const std::string &getValue() const;

    std::string toString() const;

    InternalType getInternalType() const;

    friend std::ostream &operator<<(std::ostream &os, const Token &token);

    friend bool operator==(const Token &t1, const Token &t2);

private:
    TokenType m_type;
    std::string m_value;
    InternalType m_internalType;
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

class TokenizeException : public std::exception {
public:
    explicit TokenizeException(const std::string &message) : msg(message) {}

    ~TokenizeException() noexcept override = default;

    virtual const char *what() const noexcept {
        return msg.c_str();
    }


private:
    std::string msg;
};


#endif //MASH_LEXER_H
