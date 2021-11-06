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
    num = n;
    type = valueType;
}



