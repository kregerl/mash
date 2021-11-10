#include "Collection1D.h"
#include "Value.h"
#include <set>

//--------------------
//-- Collection 1D ---
//--------------------

Collection1D::Collection1D(std::vector<int> &num) : m_value(num), m_internalType(INTEGER) {
}

Collection1D::Collection1D(std::vector<double> &num) : m_value(num), m_internalType(INTEGER) {
}

std::variant<std::vector<int>, std::vector<double>> &Collection1D::getValue() {
    return m_value;
}

std::variant<std::vector<int>, std::vector<double>> Collection1D::getValue() const {
    return m_value;
}

//--------------------
//----- Vector -------
//--------------------
Vector::Vector(std::vector<double> &num) : Collection1D(num) {}

Vector::Vector(std::vector<int> &num) : Collection1D(num) {}

int Vector::getType() const {
    return VECTOR;
}

int Vector::getInternalType() const {
    return m_internalType;
}

Vector Vector::add(Vector &vec) {
    return std::visit(overload{
            [this](std::vector<int> &s1, std::vector<int> &s2) -> Vector {
                std::vector<int> vec(s1);
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) + s2.at(i);
                }
                m_value = vec;
                return vec;
            },
            [this](auto &s1, auto &s2) -> Vector {
                std::vector<double> vec(s1.size());
                for (int i = 0; i < vec.size(); i++) {
                    vec.at(i) = s1.at(i) + s2.at(i);
                }
                m_value = vec;
                return vec;
            }
    }, m_value, vec.getValue());
}

std::ostream &operator<<(std::ostream &os, const Vector &set) {
    std::visit(overload{
            [&os](const std::vector<int> &vec) {
                for (auto &num: vec) {
                    os << num << " ";
                }
            },
            [&os](const std::vector<double> &vec) {
                for (auto &num: vec) {
                    os << num << " ";
                }
            }
    }, set.getValue());
    return os;;
}

//--------------------
//------- Set --------
//--------------------
Set::Set(std::vector<double> &num) : Collection1D(num) {}

Set::Set(std::vector<int> &num) : Collection1D(num) {}


int Set::getType() const {
    return SET;
}

int Set::getInternalType() const {
    return m_internalType;
}

Set Set::add(const int &num) {
    return std::visit(overload{
            [&num](auto &vec) -> Set {
                vec.push_back(num);
                return vec;
            }
    }, m_value);
}

Set Set::add(const double &num) {
    return std::visit(overload{
            [&num](auto &vec) -> Set {
                vec.push_back(num);
                return vec;
            }
    }, m_value);
}

Set Set::add(Set &set) {
    return std::visit(overload{
            [this](std::vector<int> &s1, std::vector<int> &s2) -> Set {
                std::vector<int> vec(s1);
                for (auto &num: s2) {
                    vec.push_back(num);
                }
                m_value = vec;
                return vec;
            },
            [this](auto &s1, auto &s2) -> Set {
                // (Double, Int) and (Double, Double)
                std::set<double> set;
                for (auto &num: s1) {
                    set.insert(num);
                }
                for (auto &num: s2) {
                    set.insert(num);
                }
                std::vector<double> vec = std::vector<double>(set.begin(), set.end());
                m_value = vec;
                return vec;
            }
    }, m_value, set.getValue());
}

// TODO: override operators so + will apply addition operation... etc.
//Set Set::sub(const int &num) {
//    return Set(std::vector());
//}
//
//Set Set::sub(const double &num) {
//    return Set(std::vector());
//}
//
//Set Set::sub(const Set &set) {
//    return Set(std::vector());
//}




std::ostream &operator<<(std::ostream &os, const Set &set) {
    std::visit(overload{
            [&os](const std::vector<int> &vec) {
                for (auto &num: vec) {
                    os << num << " ";
                }
            },
            [&os](const std::vector<double> &vec) {
                for (auto &num: vec) {
                    os << num << " ";
                }
            }
    }, set.getValue());
    return os;
}








