#ifndef MASH_VALUE_H
#define MASH_VALUE_H

#include <variant>
#include <vector>

#include "Set.h"
#include "Vector.h"


#define NONE 0x0
#define INTEGER 0x01
#define DOUBLE 0x02
#define SET 0x04
#define VECTOR 0x08
#define MATRIX 0x10

template<class... Ts>
struct overload : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overload(Ts...) -> overload<Ts...>;


// TODO: Store the type in an enum instead of bitmask, use that to determine what the "represented type" of the value will be.
// TODO: ... values are always stored as doubles, but type will be used to actually determine if it has decimal places or can be used in a function.
class Value {
public:
    Value();

    Value(double n, int valueType = DOUBLE);

    Value(Vector n);

    Value(Set n);

    Value(std::vector<double> n, int valueType);

    ~Value() = default;

public:
    std::variant<double, Vector, Set> num;
    int type;

};


#endif //MASH_VALUE_H
