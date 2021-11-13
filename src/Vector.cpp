#include "Vector.h"
#include "Value.h"
#include <cmath>

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

// Assumes the vectors are the same size.
double Vector::dot(const Vector &vec) {
    double sum = 0;
    std::vector<double> v = vec.getValue();
    for (int i = 0; i < m_value.size(); i++) {
        sum += m_value.at(i) * v.at(i);
    }
    return sum;

}

// Assumes the vectors are only 3 dimensional.
Vector Vector::cross(const Vector &vec) {
    std::vector<double> v(vec.size());
    v[0] = m_value[1] * vec.getValue()[2] - m_value[2] * vec.getValue()[1];
    v[1] = -(m_value[0] * vec.getValue()[2] - m_value[2] * vec.getValue()[0]);
    v[2] = m_value[0] * vec.getValue()[1] - m_value[1] * vec.getValue()[0];
    return v;
}

double Vector::magnitude() {
    double sum = 0;
    for (double &num: m_value) {
        sum += pow(num, 2);
    }
    return sqrt(sum);
}

Vector Vector::normalize() {
    double mag = magnitude();
    std::vector<double> v(m_value.size());
    for (int i = 0; i < m_value.size(); i++) {
        v.at(i) = m_value.at(i) / mag;
    }
    return v;
}


