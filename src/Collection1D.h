#ifndef MASH_COLLECTION1D_H
#define MASH_COLLECTION1D_H

#include <vector>
#include <variant>
#include <ostream>
#include "Number.h"


class Collection1D {
public:
    Collection1D() = default;

    explicit Collection1D(std::vector<double> &num);

    virtual ~Collection1D() = default;

    virtual NumberType getType() const;

    virtual NumberType getInternalType() const;

    std::vector<double> &getValue();

    std::vector<double> getValue() const;

    virtual void emplace_back(double n);

protected:
    NumberType m_internalType;
    std::vector<double> m_value;

};


#endif
