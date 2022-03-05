#ifndef MASH_LITERAL_H
#define MASH_LITERAL_H

#include "Lexer.h"

template<typename T>
class Literal {
public:
    explicit Literal(T value) : m_value(value) {}

    T getValue() const { return m_value; }

    void setValue(T value) { m_value = value; }

protected:
    T m_value;
};

class NumericLiteral : public Literal<double> {
public:
    NumericLiteral() : Literal(0), m_internalType(InternalType::Double) {}

    explicit NumericLiteral(double value);

    explicit NumericLiteral(double value, InternalType type);

    InternalType getInternalType() const;

    void setInternalType(InternalType type);

    friend std::ostream &operator<<(std::ostream &os, const NumericLiteral &n);

    NumericLiteral operator+(const NumericLiteral &n);

    NumericLiteral operator-(const NumericLiteral &n);

    NumericLiteral operator*(const NumericLiteral &n);

    NumericLiteral operator/(const NumericLiteral &n);

    NumericLiteral operator%(const NumericLiteral &n);

    NumericLiteral operator|(const NumericLiteral &n);

    NumericLiteral operator&(const NumericLiteral &n);

    NumericLiteral operator^(const NumericLiteral &n);

    NumericLiteral operator<<(const NumericLiteral &n);

    NumericLiteral operator>>(const NumericLiteral &n);

    inline bool operator==(const int &n) { return m_value == n; }

private:
    InternalType m_internalType;
};

// TODO: Implement StringLiterals and reading strings inside of quotes in the tokenizer
class StringLiteral : public Literal<std::string> {
public:
    explicit StringLiteral(const std::string &s);

    friend std::ostream &operator<<(std::ostream &os, const StringLiteral &s);
};

class Identifier : public Literal<std::string> {
public:
    explicit Identifier(const std::string &s);

    friend std::ostream &operator<<(std::ostream &os, const Identifier &i);
};


#endif //MASH_LITERAL_H
