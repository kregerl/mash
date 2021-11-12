#include "Collection1D.h"
#include "Value.h"
#include <algorithm>

//--------------------
//-- Collection 1D ---
//--------------------

Collection1D::Collection1D(std::vector<double> &num) : m_value(num), m_internalType(DOUBLE) {
}

int Collection1D::getType() const {
    return NONE;
}

int Collection1D::getInternalType() const {
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
















