#include "Value.h"

Value::Value() : m_num(Number()) {}


Value::Value(double n, NumberType type) : m_num(Number(n, type)) {}

Value::Value(Number n) : m_num(n) {}

Value::Value(Vector n) {
    m_num = n;
}

Value::Value(Set n) {
    m_num = n;
}

Value::Value(std::vector<double> n, NumberType type) {
    if (type == NumberType::Set) {
        m_num = Set(n);
    } else if (type == NumberType::Vector) {
        m_num = Vector(n);
    }
}

NumberType Value::getType() const {
    if (const Number *num = std::get_if<Number>(&m_num)) {
        return num->getType();
    } else if (const Number *num = std::get_if<Number>(&m_num)) {
        return num->getType();
    } else if (const Number *num = std::get_if<Number>(&m_num)) {
        return num->getType();
    }
    return NumberType::None;
}
