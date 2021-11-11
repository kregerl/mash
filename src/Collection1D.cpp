#include "Collection1D.h"
#include "Value.h"
#include <algorithm>

//--------------------
//-- Collection 1D ---
//--------------------

Collection1D::Collection1D(std::vector<int> &num) : m_value(num), m_internalType(INTEGER) {
}

Collection1D::Collection1D(std::vector<double> &num) : m_value(num), m_internalType(DOUBLE) {
}

int Collection1D::getType() const {
    return NONE;
}

int Collection1D::getInternalType() const {
    return m_internalType;
}

std::variant<std::vector<int>, std::vector<double>> &Collection1D::getValue() {
    return m_value;
}

std::variant<std::vector<int>, std::vector<double>> Collection1D::getValue() const {
    return m_value;
}

void Collection1D::emplace_back(int n) {
    std::visit(overload{
            [&n](auto &val) {
                val.emplace_back(n);
            }
    }, m_value);
}

void Collection1D::emplace_back(double n) {
    std::visit(overload{
            [&n, this](std::vector<int> &val) {
                std::vector<double> vec;
                vec.reserve(val.size());
                for (auto &num: val) {
                    vec.emplace_back(num);
                }

                vec.emplace_back(n);
                m_value = vec;
            },
            [&n](auto &val) {
                val.emplace_back(n);
            }
    }, m_value);
}
















