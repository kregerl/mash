#include "Collection1D.h"
#include "Value.h"
#include <algorithm>


Collection1D::Collection1D(std::vector<double> &num) : m_value(num), m_internalType(NumberType::Double) {}

std::vector<double>::iterator Collection1D::begin() {
    return m_value.begin();
}

std::vector<double>::iterator Collection1D::end() {
    return m_value.end();
}

NumberType Collection1D::getType() const {
    return NumberType::None;
}

NumberType Collection1D::getInternalType() const {
    return m_internalType;
}

std::vector<double> &Collection1D::getValue() {
    return m_value;
}

std::vector<double> Collection1D::getValue() const {
    return m_value;
}

void Collection1D::emplace_back(double n) {
    m_value.emplace_back(n);
}

size_t Collection1D::size() const {
    return m_value.size();
}

double Collection1D::min() {
    double min = m_value.front();
    for (auto &num : m_value) {
        if (min > num) {
            min = num;
        }
    }
    return min;
}

double Collection1D::max() {
    double max = 0;
    for (auto &num : m_value) {
        if (max < num) {
            max = num;
        }
    }
    return max;
}


















