#ifndef MASH_VALUE_H
#define MASH_VALUE_H

#include <variant>
#include <vector>



enum class ValueType {
    None = 0, Integer, Double, Set, Vector, Matrix
};

class Value {
public:
    Value();
    Value(int n, ValueType valueType = ValueType::Integer);
    Value(double n, ValueType valueType = ValueType::Double);
    Value(std::vector<double> n, ValueType valueType);
    ~Value() = default;
public:
    std::variant<int, double, std::vector<double>> num;
    ValueType type;
};


#endif //MASH_VALUE_H
