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
    } else if (const Vector *vec = std::get_if<Vector>(&m_num)) {
        return vec->getType();
    } else if (const Set *set = std::get_if<Set>(&m_num)) {
        return set->getType();
    }
    return NumberType::None;
}

void Value::setNum(const Value &n) {
    m_num = n.m_num;
}

std::variant<Number, Vector, Set> &Value::getNum() {
    return m_num;
}


void Value::setMessage(const std::string &s) {
    m_messaage = s;
}


std::optional<std::string> Value::getMessage() {
    return m_messaage;
}

void Value::setError(const std::string &s) {
    m_error = s;
}


std::optional<std::string> Value::getError() {
    return m_error;
}

std::ostream &operator<<(std::ostream &os, const Value &val) {
    if (const Number *num = std::get_if<Number>(&val.m_num)) {
        if (val.m_error) {
            os << "Error: " << val.m_error->c_str() << std::endl;
        } else {
            if (val.m_messaage) {
                os << val.m_messaage->c_str() << std::endl;
            }
            os << *num;
        }
    } else if (const Vector *vec = std::get_if<Vector>(&val.m_num)) {
        if (val.m_error) {
            os << "Error: " << val.m_error->c_str() << std::endl;
        } else {
            if (val.m_messaage) {
                os << val.m_messaage->c_str() << std::endl;
            }
            os << *vec;
        }
    } else if (const Set *set = std::get_if<Set>(&val.m_num)) {
        if (val.m_error) {
            os << "Error: " << val.m_error->c_str() << std::endl;
        } else {
            if (val.m_messaage) {
                os << val.m_messaage->c_str() << std::endl;
            }
            os << *set;
        }
    }
    return os;
}

Value &Value::operator=(const Value &val) {
    m_num = val.m_num;
    return *this;
}

Value &Value::operator=(const double &val) {
    m_num = Number(val);
    return *this;
}




