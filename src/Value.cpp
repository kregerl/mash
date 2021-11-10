#include "Value.h"

Value::Value() : num(0), type(NONE) {
}

Value::Value(int n, int valueType) {
    num = n;
    type = valueType;
}

Value::Value(double n, int valueType) {
    num = n;
    type = valueType;
}

Value::Value(std::vector<double> n, int valueType) {
    if (valueType == SET) {
        num = Set(n);
    } else if (valueType == VECTOR) {
        num = Vector(n);
    }
    type = valueType;
}

Value::Value(Vector n) {
    num = n;
    type = n.getType();
}

Value::Value(Set n) {
    num = n;
    type = n.getType();
}
