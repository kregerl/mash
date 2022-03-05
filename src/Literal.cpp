#include "Literal.h"
#include "Nodes.h"
#include <string>
#include <sstream>

NumericLiteral::NumericLiteral(double value) : Literal(value), m_internalType(InternalType::Double) {}

NumericLiteral::NumericLiteral(double value, InternalType type) : Literal(value), m_internalType(type) {}

InternalType NumericLiteral::getInternalType() const {
    return m_internalType;
}

void NumericLiteral::setInternalType(InternalType type) {
    this->m_internalType = type;
}

std::ostream &operator<<(std::ostream &os, const NumericLiteral &n) {
    std::stringstream ss;
    ss << n.getValue() << " (" << internalTypeStrings[static_cast<int>(n.getInternalType())] << ")";
    os << ss.str();
    return os;
}

NumericLiteral NumericLiteral::operator+(const NumericLiteral &n) {
    return NumericLiteral(m_value + n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator-(const NumericLiteral &n) {
    return NumericLiteral(m_value - n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator*(const NumericLiteral &n) {
    return NumericLiteral(m_value * n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator/(const NumericLiteral &n) {
    return NumericLiteral(m_value / n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator%(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) % static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform modulo operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

NumericLiteral NumericLiteral::operator|(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) | static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform bitwise or operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

NumericLiteral NumericLiteral::operator&(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) & static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform bitwise and operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

NumericLiteral NumericLiteral::operator^(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) ^ static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform bitwise xor operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

NumericLiteral NumericLiteral::operator<<(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) << static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform bitshift left operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

NumericLiteral NumericLiteral::operator>>(const NumericLiteral &n) {
    if (m_internalType > InternalType::Double && n.getInternalType() > InternalType::Double) {
        return NumericLiteral(static_cast<int>(m_value) >> static_cast<int>(n.getValue()),
                              std::min(m_internalType, n.getInternalType()));
    } else {
        throw EvaluatorException(
                "Cannot perform bitshift right operation between numerics of types " +
                internalTypeToString(m_internalType) + " and " +
                internalTypeToString(n.getInternalType()));
    }
}

StringLiteral::StringLiteral(const std::string &s) : Literal(s) {}
