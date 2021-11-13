#ifndef MASH_NUMBER_H
#define MASH_NUMBER_H

#include <ostream>

enum class NumberType {
    None = 0,
    Integer = 0x01,
    Double = 0x02,
    IntegerOrDouble = 0x03,
    Set = 0x04,
    SetOrInteger = 0x05,
    SetOrDouble = 0x06,
    SetOrIntegerOrDouble = 0x07,
    Vector = 0x08,
    VectorOrInteger = 0x09,
    VectorOrDouble = 0xA,
    VectorOrSet = 0xB,
    VectorOrIntegerOrDouble = 0xC,
    VectorOrSetOrInteger = 0xD,
    VectorOrSetOrDouble = 0xE,
    VectorOrSetOrIntegerOrDouble = 0xF
};

inline constexpr NumberType
operator&(NumberType x, NumberType y) {
    return static_cast<NumberType>
    (static_cast<int>(x) & static_cast<int>(y));
}

inline constexpr NumberType
operator|(NumberType x, NumberType y) {
    return static_cast<NumberType>
    (static_cast<int>(x) | static_cast<int>(y));
}

inline constexpr NumberType
operator^(NumberType x, NumberType y) {
    return static_cast<NumberType>
    (static_cast<int>(x) ^ static_cast<int>(y));
}

inline std::ostream &operator<<(std::ostream &os, NumberType y) {
    os << static_cast<int>(y);
    return os;
}


class Number {
public:
    Number();

    explicit Number(double value, NumberType type = NumberType::Double);

    NumberType getType() const;

    double getRawDouble() const;

    Number operator+(const Number &num);

    Number operator-(const Number &num);

    Number operator*(const Number &num);

    Number operator/(const Number &num);

    Number operator%(const Number &num);

    Number operator&(const Number &num);

    Number operator|(const Number &num);

    Number operator^(const Number &num);

    NumberType opResultType(const Number &num) const;

private:
    double m_value;
    NumberType m_type;
};


#endif //MASH_NUMBER_H
