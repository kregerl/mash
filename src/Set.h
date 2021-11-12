#ifndef MASH_SET_H
#define MASH_SET_H

#include "Collection1D.h"

class SetLayout {
public:
    enum class Layout {
        Single = 0, Pair
    };

    SetLayout(Layout layout);

    void printContents(std::ostream &os, const std::vector<double> &vec) const;

private:
    Layout m_layout;
};

class Set : public Collection1D {
public:
    Set();

    explicit Set(std::vector<double> &num, SetLayout layout = SetLayout::Layout::Single);

    explicit Set(Collection1D &num, SetLayout layout = SetLayout::Layout::Single);

    int getType() const override;

    int getInternalType() const override;

    const SetLayout &getLayout() const;

    friend std::ostream &operator<<(std::ostream &os, const Set &set);

    Set operator+(const Set &vec);

    Set operator-(const Set &vec);

    Set add(const Set &set);

    Set sub(const Set &set);

    Set scalarMul(const double &num);

    Set cartesianProduct(const Set &set);

private:
    SetLayout m_layout;
};


#endif //MASH_SET_H
