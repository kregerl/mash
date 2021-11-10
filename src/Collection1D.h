#ifndef MASH_COLLECTION1D_H
#define MASH_COLLECTION1D_H

#include <vector>
#include <variant>
#include <ostream>


template<class... Ts>
struct overload : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overload(Ts...) -> overload<Ts...>;

class Collection1D {
public:
    Collection1D() = default;

    explicit Collection1D(std::vector<int> &num);

    explicit Collection1D(std::vector<double> &num);

    virtual ~Collection1D() = default;

    virtual int getType() const = 0;

    virtual int getInternalType() const = 0;

    std::variant<std::vector<int>, std::vector<double>> &getValue();

    std::variant<std::vector<int>, std::vector<double>> getValue() const;



protected:
    int m_internalType;
    std::variant<std::vector<int>, std::vector<double>> m_value;

};

class Vector : Collection1D {
public:
    Vector() = default;

    Vector(std::vector<int> &num);

    Vector(std::vector<double> &num);

    int getType() const override;

    int getInternalType() const override;

    friend std::ostream &operator<<(std::ostream &os, const Vector &set);

    Vector add(Vector &vec);
};

class Set : Collection1D {
public:
    Set() = default;

    Set(std::vector<int> &num);

    Set(std::vector<double> &num);

    int getType() const override;

    int getInternalType() const override;

    friend std::ostream &operator<<(std::ostream &os, const Set &set);

    Set add(const int &num);

    Set add(const double &num);

    Set add(Set &set);

    Set sub(const int &num);

    Set sub(const double &num);

    Set sub(const Set &set);
};

#endif
