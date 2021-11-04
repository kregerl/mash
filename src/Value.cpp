#include "Value.h"

Value::Value() : num(0), type(ValueType::Integer) {
}
Value::Value(int n, ValueType valueType) {
    num = n;
    type = valueType;
}
Value::Value(double n, ValueType valueType) {
    num = n;
    type = valueType;
}
Value::Value(std::vector<double> n, ValueType valueType) {
    num = n;
    type = valueType;
}



