#ifndef MASH_SET_H
#define MASH_SET_H

#include "Collection1D.h"

class Set : public Collection1D {
public:
    Set() = default;

    Set(std::vector<int> &num);

    Set(std::vector<double> &num);

    Set(Collection1D &num);

    int getType() const override;

    int getInternalType() const override;

    friend std::ostream &operator<<(std::ostream &os, const Set &set);

    Set operator+(const Set &vec);

    Set operator-(const Set &vec);

    Set add(const Set &set);

    Set sub(const Set &set);
};


#endif //MASH_SET_H
