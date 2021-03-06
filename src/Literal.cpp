#include "Literal.h"
#include "Nodes.h"
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <algorithm>

NumericLiteral::NumericLiteral(double value) : Literal(value), m_internalType(InternalType::Double) {}

NumericLiteral::NumericLiteral(double value, InternalType type) : Literal(value), m_internalType(type) {}

InternalType NumericLiteral::getInternalType() const {
    return m_internalType;
}

void NumericLiteral::setInternalType(InternalType type) {
    this->m_internalType = type;
}

std::ostream& operator<<(std::ostream& os, const NumericLiteral& n) {
    std::stringstream ss;
    switch (n.getInternalType()) {
        case InternalType::Double: {
            ss << std::setprecision(32) << n.getValue();
            break;
        }
        case InternalType::Integer: {
            ss << std::setprecision(32) << long(n.getValue());
            break;
        }
        case InternalType::Hex: {
            ss << "0x" << std::hex << long(n.getValue());
            break;
        }
        case InternalType::Binary: {
            std::string bin;
            int value = int(n.getValue());
            while (value != 0) {
                bin = (value % 2 == 0 ? "0" : "1") + bin;
                value /= 2;
            }
            ss << "0b" << bin;
            break;
        }
    }
    os << ss.str();
    return os;
}

NumericLiteral NumericLiteral::operator+(const NumericLiteral& n) {
    return NumericLiteral(m_value + n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator-(const NumericLiteral& n) {
    return NumericLiteral(m_value - n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator*(const NumericLiteral& n) {
    return NumericLiteral(m_value * n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator/(const NumericLiteral& n) {
    return NumericLiteral(m_value / n.getValue(), std::min(m_internalType, n.getInternalType()));
}

NumericLiteral NumericLiteral::operator%(const NumericLiteral& n) {
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

NumericLiteral NumericLiteral::operator|(const NumericLiteral& n) {
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

NumericLiteral NumericLiteral::operator&(const NumericLiteral& n) {
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

NumericLiteral NumericLiteral::operator^(const NumericLiteral& n) {
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

NumericLiteral NumericLiteral::operator<<(const NumericLiteral& n) {
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

NumericLiteral NumericLiteral::operator>>(const NumericLiteral& n) {
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

void NumericLiteral::operator+=(const NumericLiteral& n) {
    m_value += n.getValue();
}

StringLiteral::StringLiteral() : Literal("") {};

StringLiteral::StringLiteral(const std::string& s) : Literal(s) {}

StringLiteral::StringLiteral(const char& c) : Literal(std::to_string(c)) {}


std::ostream& operator<<(std::ostream& os, const StringLiteral& s) {
    os << s.getValue();
    return os;
}

StringLiteral StringLiteral::operator+(const StringLiteral& n) {
    return StringLiteral(m_value + n.getValue());
}

StringLiteral StringLiteral::operator+(const std::string& n) {
    return StringLiteral(m_value + n);
}

StringLiteral StringLiteral::operator*(const NumericLiteral& n) {
    if (n.getInternalType() > InternalType::Double) {
        StringLiteral s;
        for (int i = 0; i < n.getValue(); i++) {
            s = s + m_value;
        }
        return s;
    }
    throw EvaluatorException("Cannot multiply a string by a decimal value!");
}

StringLiteral StringLiteral::operator-(const StringLiteral& n) {
    std::string s = m_value;
    size_t pos = std::string::npos;
    while ((pos = s.find(n.getValue())) != std::string::npos) {
        s.erase(pos, n.getValue().length());
    }
    return StringLiteral(s);
}

StringLiteral StringLiteral::operator[](int i) {
    if (i > m_value.size()) {
        throw EvaluatorException("Index out of bounds for StringLiteral of size " + std::to_string(m_value.size()));
    }
    return StringLiteral(m_value.at(i));
}

StringLiteral StringLiteral::operator+(const char& n) {
    return StringLiteral(m_value + n);
}

StringLiteral StringLiteral::operator<<(const NumericLiteral& n) {
    if (n.getInternalType() > InternalType::Double) {
        int val = static_cast<int>(n.getValue());
        std::string s = m_value.substr(val, m_value.size()) + m_value.substr(0, val);
        return StringLiteral(s);
    } else {
        throw EvaluatorException("String shifts are only supported for integer types!");
    }

}

StringLiteral StringLiteral::operator>>(const NumericLiteral& n) {
    if (n.getInternalType() > InternalType::Double) {
        int val = static_cast<int>(n.getValue());
        std::string s = m_value.substr(m_value.size() - val, val) +
                        m_value.substr(0, m_value.size() - val);
        return StringLiteral(s);
    } else {
        throw EvaluatorException("String shifts are only supported for integer types!");
    }
}

StringLiteral StringLiteral::asHex(StringLiteral& s) {
    std::stringstream ss;
    ss << "0x";
    for (auto const& ch : s.getValue()) {
        ss << std::hex << static_cast<int>(ch);
    }

    return StringLiteral(ss.str());
}

StringLiteral StringLiteral::asBin(StringLiteral& s) {
    std::stringstream ss;

    for (auto const& ch : s.getValue()) {
        std::string bin;
        auto value = static_cast<unsigned char>(ch);
        while (value != 0) {
            bin += (value % 2 == 0 ? "0" : "1");
            value /= 2;
        }
        std::reverse(bin.begin(), bin.end());
        ss << '0' << bin << ' ';
    }
    return StringLiteral(ss.str());
}

