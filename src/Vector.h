#ifndef MASH_VECTOR_H
#define MASH_VECTOR_H

#include "Collection1D.h"

class Vector : public Collection1D {
public:
    Vector() = default;

    Vector(std::vector<double> &num);

    Vector(Collection1D &num);

    int getType() const override;

    int getInternalType() const override;

    friend std::ostream &operator<<(std::ostream &os, const Vector &vec);

    Vector operator+(const Vector &vec);

    Vector operator-(const Vector &vec);

    Vector add(const Vector &vec);

    Vector sub(const Vector &vec);

    Vector scalarMul(const double &val);

    double dot(const Vector &vec);

};


#endif //MASH_VECTOR_H
