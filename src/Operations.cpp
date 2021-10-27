#include "Operations.h"
#include <cmath>

Result noOp(std::stack<Op> &ops, std::stack<double> &values) {
    ops.pop();
    Result result = DEFAULT_RESULT;
    result.error = false;
    return result;
}

Result opAdd(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = values.top();
        values.pop();
        double num2 = values.top();
        values.pop();
        result.num = num1 + num2;
        result.error = false;
    }
    return result;
}

Result opSub(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = values.top();
        values.pop();
        double num2 = values.top();
        values.pop();
        result.num = num1 - num2;
        result.error = false;
    }
    return result;
}
Result opMul(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = values.top();
        values.pop();
        double num2 = values.top();
        values.pop();
        result.num = num1 * num2;
        result.error = false;
    }
    return result;
}
Result opDiv(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = values.top();
        values.pop();
        double num2 = values.top();
        values.pop();
        result.error = false;
        if (num1 == 0) {
            printf("Error, division by zero");
            result.error = true;
            return result;
        }
        result.num = num2 / num1;
    }
    return result;
}
Result opMod(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(values.top());
        values.pop();
        int num2 = static_cast<int>(values.top());
        values.pop();
        result.error = false;
        result.num = num2 % num1;
    }
    return result;
}

Result opExp(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = values.top();
        values.pop();
        double num2 = values.top();
        values.pop();
        result.error = false;
        result.num = pow(num2, num1);
    }
    return result;
}
Result opSqrt(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = values.top();
        values.pop();
        result.error = false;
        result.num = sqrt(num);
    }
    return result;
}
Result opBand(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(values.top());
        values.pop();
        int num2 = static_cast<int>(values.top());
        values.pop();
        result.error = false;
        result.num = num1 & num2;
    }
    return result;
}
Result opBor(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(values.top());
        values.pop();
        int num2 = static_cast<int>(values.top());
        values.pop();
        result.error = false;
        result.num = num1 | num2;
    }
    return result;
}
Result opBxor(std::stack<Op> &ops, std::stack<double> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(values.top());
        values.pop();
        int num2 = static_cast<int>(values.top());
        values.pop();
        result.error = false;
        result.num = num1 ^ num2;
    }
    return result;
}
