#include "Set.h"
#include "Value.h"
#include <set>
#include <algorithm>

Set::Set(std::vector<double> &num) : Collection1D(num) {}

Set::Set(std::vector<int> &num) : Collection1D(num) {}

Set::Set(Collection1D &num) : Collection1D(num) {}

int Set::getType() const {
    return SET;
}

int Set::getInternalType() const {
    return m_internalType;
}

std::ostream &operator<<(std::ostream &os, const Set &set) {
    std::visit(overload{
            [&os](const auto &set) {
                os << '{';
                for (int i = set.size() - 1; i >= 0; i--) {
                    if (i == 0) {
                        os << set.at(i);
                    } else {
                        os << set.at(i) << ", ";
                    }
                }
                os << '}';
            }
    }, set.getValue());
    return os;
}

Set Set::operator+(const Set &vec) {
    Set tmp(*this);
    tmp.add(vec);
    return tmp;
}

Set Set::operator-(const Set &vec) {
    Set tmp(*this);
    tmp.sub(vec);
    return tmp;
}

Set Set::add(const Set &set) {
    return std::visit(overload{
            [this](std::vector<int> &s1, const std::vector<int> &s2) -> Set {
                std::set<int> set;
                for (auto &num1: s1) {
                    for (auto &num2: s2) {
                        set.insert(num1 + num2);
                    }
                }
                std::vector<int> vec = std::vector<int>(set.begin(), set.end());
                m_value = vec;
                m_internalType = INTEGER;
                return vec;
            },
            [this](auto &s1, const auto &s2) -> Set {
                std::set<double> set;
                for (auto &num1: s1) {
                    for (auto &num2: s2) {
                        set.insert(num1 + num2);
                    }
                }
                std::vector<double> vec = std::vector<double>(set.begin(), set.end());
                m_value = vec;
                m_internalType = DOUBLE;
                return vec;
            }
    }, m_value, set.getValue());
}

Set Set::sub(const Set &set) {
    return std::visit(overload{
            [this](std::vector<int> &s1, const std::vector<int> &s2) -> Set {
                std::set<int> set;
                for (int &num: s1) {
                    if (std::find(s2.begin(), s2.end(), num) == s2.end()) {
                        set.insert(num);
                    }
                }
                std::vector<int> vec = std::vector<int>(set.begin(), set.end());
                m_value = vec;
                m_internalType = INTEGER;
                return vec;
            },
            [this](auto &s1, const auto &s2) -> Set {
                std::set<double> set;
                for (auto &num: s1) {
                    if (std::find(s2.begin(), s2.end(), num) == s2.end()) {
                        set.insert(num);
                    }
                }
                std::vector<double> vec = std::vector<double>(set.begin(), set.end());
                m_value = vec;
                m_internalType = DOUBLE;
                return vec;
            }
    }, m_value, set.getValue());
}