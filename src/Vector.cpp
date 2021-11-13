#include "Vector.h"
#include "Value.h"

Vector::Vector(std::vector<double> &num) : Collection1D(num) {}

Vector::Vector(Collection1D &num) : Collection1D(num) {}

NumberType Vector::getType() const {
    return NumberType::Vector;
}

NumberType Vector::getInternalType() const {
    return m_internalType;
}

std::ostream &operator<<(std::ostream &os, const Vector &vec) {
    std::vector<double> values = vec.getValue();
    os << '[';
    for (int i = values.size() - 1; i >= 0; i--) {
        if (i == 0) {
            os << values.at(i);
        } else {
            os << values.at(i) << ", ";
        }
    }
    os << ']';
    return os;
}

Vector Vector::operator+(const Vector &vec) {
    Vector tmp(*this);
    tmp = tmp.add(vec);
    return tmp;
}

Vector Vector::operator-(const Vector &vec) {
    Vector tmp(*this);
    tmp = tmp.sub(vec);
    return tmp;
}

Vector Vector::add(const Vector &vec) {
    std::vector<double> v(m_value.size());
    for (int i = 0; i < v.size(); i++) {
        v.at(i) = m_value.at(i) + vec.getValue().at(i);
    }
    return v;
}

Vector Vector::sub(const Vector &vec) {
    std::vector<double> v(m_value.size());
    for (int i = 0; i < v.size(); i++) {
        v.at(i) = m_value.at(i) - vec.getValue().at(i);
    }
    return v;
}

Vector Vector::scalarMul(const double &val) {
    std::vector<double> vec(m_value.size());
    for (auto &num: m_value) {
        vec.emplace_back(num * val);
    }
    return vec;
}

double Vector::dot(const Vector &vec) {
    double sum = 0;
    std::vector<double> v = vec.getValue();
    for (int i = 0; i < m_value.size(); i++) {
        sum += m_value.at(i) * v.at(i);
    }
    return sum;

}


