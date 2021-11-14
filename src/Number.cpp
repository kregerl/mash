#include "Number.h"

Number::Number() : m_value(0), m_type(NumberType::Double) {}

Number::Number(int value, NumberType type) : m_value(value), m_type(type) {}

Number::Number(double value, NumberType type) : m_value(value), m_type(type) {}

NumberType Number::getType() const {
    return m_type;
}

double Number::getRawDouble() const {
    return m_value;
}

Number Number::operator+(const Number &num) const {
    return Number(m_value + num.getRawDouble(), opResultType(num));
}

Number Number::operator+(const double &num) const {
    return Number(m_value + num, NumberType::Double);
}

Number &Number::operator+=(const Number &num) {
    m_value += num.getRawDouble();
    return *this;
}

Number &Number::operator+=(const double &num) {
    m_value += num;
    return *this;
}

Number Number::operator-(const Number &num) const {
    return Number(m_value - num.getRawDouble(), opResultType(num));
}

Number Number::operator*(const Number &num) const {
    return Number(m_value * num.getRawDouble(), opResultType(num));
}

Number Number::operator*(const double &num) const {
    return Number(m_value * num, NumberType::Double);
}

Number Number::operator/(const Number &num) const {
    return Number(m_value / num.getRawDouble(), opResultType(num));
}

Number Number::operator%(const Number &num) const {
    return Number(static_cast<int>(m_value) % static_cast<int>(num.getRawDouble()), opResultType(num));
}

Number Number::operator&(const Number &num) const {
    return Number(static_cast<int>(m_value) & static_cast<int>(num.getRawDouble()), opResultType(num));
}

Number Number::operator|(const Number &num) const {
    return Number(static_cast<int>(m_value) | static_cast<int>(num.getRawDouble()), opResultType(num));
}

Number Number::operator^(const Number &num) const {
    return Number(static_cast<int>(m_value) ^ static_cast<int>(num.getRawDouble()), opResultType(num));
}

NumberType Number::opResultType(const Number &num) const {
    if (m_type == num.m_type) {
        return m_type;
    } else if ((m_type == NumberType::Double || m_type == NumberType::Integer) &&
               (num.m_type == NumberType::Double || num.m_type == NumberType::Integer)) {
        return NumberType::Double;
    }
    return NumberType::None;
}











