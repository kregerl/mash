#ifndef MASH_NUMBER_H
#define MASH_NUMBER_H

#include <ostream>

const std::string typeStrings[] = {"None", "Integer", "Double", "Vector", "Set", "Matrix"};
enum class NumberType {
    None = 0, Integer, Double, Vector, Set, Matrix
};

inline std::ostream &operator<<(std::ostream &os, NumberType y) {
    os << typeStrings[static_cast<int>(y)];
    return os;
}


class Number {
public:
    Number();

    explicit Number(int value, NumberType type = NumberType::Integer);

    explicit Number(double value, NumberType type = NumberType::Double);

    NumberType getType() const;

    double getRawDouble() const;

    friend std::ostream &operator<<(std::ostream &os, const Number &n);

    Number operator+(const Number &num) const;

    Number operator+(const double &num) const;

    Number &operator+=(const Number &num);

    Number &operator+=(const double &num);

    Number operator-(const Number &num) const;

    Number operator*(const Number &num) const;

    Number operator*(const double &num) const;

    Number operator/(const Number &num) const;

    Number operator%(const Number &num) const;

    Number operator&(const Number &num) const;

    Number operator|(const Number &num) const;

    Number operator^(const Number &num) const;

    NumberType opResultType(const Number &num) const;

private:
    double m_value;
    NumberType m_type;
};


#endif //MASH_NUMBER_H
