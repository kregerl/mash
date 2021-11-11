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

    virtual int getType() const;

    virtual int getInternalType() const;

    std::variant<std::vector<int>, std::vector<double>> &getValue();

    std::variant<std::vector<int>, std::vector<double>> getValue() const;

    virtual void emplace_back(int n);

    virtual void emplace_back(double n);

protected:
    int m_internalType;
    std::variant<std::vector<int>, std::vector<double>> m_value;

};

#endif
