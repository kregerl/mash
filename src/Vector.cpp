#include "Vector.h"
#include "Value.h"

Vector::Vector(std::vector<double> &num) : Collection1D(num) {}

Vector::Vector(std::vector<int> &num) : Collection1D(num) {}

Vector::Vector(Collection1D &num) : Collection1D(num) {}

int Vector::getType() const {
    return VECTOR;
}

int Vector::getInternalType() const {
    return m_internalType;
}

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
    std::visit(overload{
            [&os](const auto &vec) {
                os << '[';
                for (int i = vec.size() - 1; i >= 0; i--) {
                    if (i == 0) {
                        os << vec.at(i);
                    } else {
                        os << vec.at(i) << ", ";
                    }
                }
                os << ']';
            }
    }, vec.getValue());
    return os;
}

Vector Vector::operator+(const Vector &vec) {
    Vector tmp(*this);
    tmp.add(vec);
    return tmp;
}

Vector Vector::operator-(const Vector &vec) {
    Vector tmp(*this);
    tmp.sub(vec);
    return tmp;
}

Vector Vector::add(const Vector &vec) {
    return std::visit(overload{
            [this](std::vector<int> &s1, const std::vector<int> &s2) -> Vector {
                std::vector<int> vec(s1);
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) + s2.at(i);
                }
                m_value = vec;
                m_internalType = INTEGER;
                return vec;
            },
            [this](auto &s1, const auto &s2) -> Vector {
                std::vector<double> vec(s1.size());
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) + s2.at(i);
                }
                m_value = vec;
                m_internalType = DOUBLE;
                return vec;
            }
    }, m_value, vec.getValue());
}

Vector Vector::sub(const Vector &vec) {
    return std::visit(overload{
            [this](std::vector<int> &s1, const std::vector<int> &s2) -> Vector {
                std::vector<int> vec(s1);
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) - s2.at(i);
                }
                m_value = vec;
                m_internalType = INTEGER;
                return vec;
            },
            [this](auto &s1, const auto &s2) -> Vector {
                std::vector<double> vec(s1.size());
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) - s2.at(i);
                }
                m_value = vec;
                m_internalType = DOUBLE;
                return vec;
            }
    }, m_value, vec.getValue());
}


