#ifndef MASH_VALUE_H
#define MASH_VALUE_H

#include <variant>
#include <vector>
#include "Vector.h"
#include "Set.h"

#define NONE 0x0
#define INTEGER 0x01
#define DOUBLE 0x02
#define SET 0x04
#define VECTOR 0x08
#define MATRIX 0x10


class Value {
public:
    Value();

    Value(int n, int valueType = INTEGER);

    Value(double n, int valueType = DOUBLE);

    Value(Vector n);

    Value(Set n);

    Value(std::vector<double> n, int valueType);

    ~Value() = default;

public:
    std::variant<int, double, Vector, Set> num;
    int type;

};


#endif //MASH_VALUE_H
