#include "Set.h"
#include "Value.h"
#include <set>
#include <algorithm>
#include <iostream>

Set::Set() : m_layout(SetLayout::Layout::Single) {}

Set::Set(std::vector<double> &num, SetLayout layout) : Collection1D(num), m_layout(layout) {}

Set::Set(Collection1D &num, SetLayout layout) : Collection1D(num), m_layout(layout) {}

NumberType Set::getType() const {
    return NumberType::Set;
}

const SetLayout &Set::getLayout() const {
    return m_layout;
}

std::ostream &operator<<(std::ostream &os, const Set &set) {
    std::vector<double> values = set.getValue();
    set.getLayout().printContents(os, values);
    return os;
}

Set Set::operator+(const Set &vec) {
    Set tmp(*this);
    tmp = tmp.add(vec);
    return tmp;
}

Set Set::operator-(const Set &vec) {
    Set tmp(*this);
    tmp = tmp.sub(vec);
    return tmp;
}

Set Set::add(const Set &set) {
    std::vector<double> s2 = set.getValue();
    std::set<double> s;
    for (auto &num1: m_value) {
        for (auto &num2: s2) {
            s.insert(num1 + num2);
        }
    }
    std::vector<double> vec = std::vector<double>(s.begin(), s.end());
    return Set(vec);
}

Set Set::sub(const Set &set) {
    std::vector<double> s2 = set.getValue();
    std::set<double> s;
    for (auto &num: m_value) {
        if (std::find(s2.begin(), s2.end(), num) == s2.end()) {
            s.insert(num);
        }
    }
    std::vector<double> vec = std::vector<double>(s.begin(), s.end());
    return Set(vec);
}

Set Set::scalarMul(const double &num) {
    std::set<double> set;
    for (auto &s: m_value) {
        set.insert(s * num);
    }
    std::vector<double> vec = std::vector<double>(set.begin(), set.end());
    return Set(vec);
}

Set Set::cartesianProduct(const Set &set) {
    std::vector<double> vec;
    for (double &s: m_value) {
        for (double &s1: set.getValue()) {
            vec.push_back(s);
            vec.push_back(s1);
        }
    }
    return Set(vec, SetLayout::Layout::Pair);
}


//---------------------
//----- SetLayout -----
//---------------------
SetLayout::SetLayout(SetLayout::Layout layout) : m_layout(layout) {}

void SetLayout::printContents(std::ostream &os, const std::vector<double> &vec) const {
    if (m_layout == Layout::Single) {
        os << '{';
        for (int i = vec.size() - 1; i >= 0; i--) {
            if (i == 0) {
                os << vec.at(i);
            } else {
                os << vec.at(i) << ", ";
            }
        }
        os << '}';
    } else if (m_layout == Layout::Pair) {
        if (vec.size() % 2 == 0) {
            os << '{';
            for (int i = vec.size() - 1; i >= 0; i--) {
                if (i >= 1) {
                    os << '(';
                    os << vec.at(i);
                    os << ", " << vec.at(--i);
                    os << ')';
                }
                if (i > 0) {
                    os << ", ";
                }
            }
            os << '}';
        } else {
            os << "Cannot have a pair layout on a set with an odd number of elements";
        }
    }
}
