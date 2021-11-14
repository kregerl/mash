#include "Operations.h"

Result noOp(std::stack<Op> &ops, std::stack<Value> &values) {
    ops.pop();
    Result result = DEFAULT_RESULT;
//    result.error = false;
    return result;
}

Result opAdd(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        std::cout << num1.getType() << std::endl;
        std::cout << num2.getType() << std::endl;

        result.num = std::visit(overload{
                [](Number &a, Number &b) -> Value { return {a + b}; },
                [](Vector &a, Vector &b) -> Value { return a + b; },
                [](Set &a, Set &b) -> Value { return a + b; },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.error = "Unsupported operation: Cannot add type of " +
                                   typeStrings[static_cast<int>(num1.getType())] + " to " +
                                   typeStrings[static_cast<int>(num2.getType())] + ".";
                    return 0;
                }
        }, num1.m_num, num2.m_num);
    }
    return result;
}


Result opSub(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        result.num = std::visit(overload{
                [](Number &a, Number &b) -> Value { return b - a; },
                [](Vector &a, Vector &b) -> Value { return b - a; },
                [](Set &a, Set &b) -> Value { return b - a; },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.error = "Unsupported operation: Cannot subtract type of " +
                                   typeStrings[static_cast<int>(num1.getType())] + " to " +
                                   typeStrings[static_cast<int>(num2.getType())] + ".";
                    return 0;
                }
        }, num1.m_num, num2.m_num);
    } else if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [](Number &a) -> Value { return a * Number(-1); },
                [](Vector &a) -> Value { return a.scalarMul(-1); },
                [](Set &a) -> Value { return a.scalarMul(-1); },
                [&result](auto &a) -> Value {
                    result.error = "Unsupported operation: This should never happen.";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}

Result opMul(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        result.num = std::visit(overload{
                [](Number &a, Number &b) -> Value { return b * a; },
                [](Number &a, Vector &b) -> Value { return b.scalarMul(a.getRawDouble()); },
                [](Number &a, Set &b) -> Value { return b.scalarMul(a.getRawDouble()); },
                [](Vector &a, Number &b) -> Value { return a.scalarMul(b.getRawDouble()); },
                [](Vector &a, Vector &b) -> Value { return a.dot(b); },
                [](Set &a, Number &b) -> Value { return a.scalarMul(b.getRawDouble()); },
                [](Set &a, Set &b) -> Value { return a.cartesianProduct(b); },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.error = "Unsupported operation: Cannot multiply type of " +
                                   typeStrings[static_cast<int>(num1.getType())] + " to " +
                                   typeStrings[static_cast<int>(num2.getType())] + ".";
                    return 0;
                }
        }, num1.m_num, num2.m_num);

    }
    return result;
}

Result opDiv(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Number num1 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        Number num2 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        if (num1.getRawDouble() == 0) {
            result.error = "Error, division by zero.";
            return result;
        }
        result.num = num2.getRawDouble() / num1.getRawDouble();
    }
    return result;
}

Result opMod(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    Op op = ops.top();
    std::string token = ops.top().token;
    ops.pop();

    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(num2 % num1), NumberType::Integer};
    }
//    else if (token == "mod") {
//        std::cout << "Mod: `mod(a, b)` returns the result of `a mod b`. Can also be represented as `(a % b)`" << std::endl;
//        result.error = false;
//    }
    return result;
}

Result opExp(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Number num1 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        Number num2 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        result.num = {pow(num2.getRawDouble(), num1.getRawDouble()), num1.opResultType(num2)};
    }
    return result;
}

Result opSqrt(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [](Number &a) -> Value { return sqrt(a.getRawDouble()); },
                [](Vector &a) -> Value { return a.sqrt(); },
                [&result, &num](auto &a) -> Value {
                    result.error = "Unsupported operation: Cannot take the square root of a " +
                                   typeStrings[static_cast<int>(num.getType())] + ".";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}

Result opSin(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Number num = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        result.num = sin(num.getRawDouble());
        std::cout << "**NOTE** Inputs to the sin function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCos(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Number num = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        result.num = cos(num.getRawDouble());
    }
    return result;
}

Result opBand(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(num1 & num2), NumberType::Integer};
    }
    return result;
}

Result opBor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(num1 | num2), NumberType::Integer};
    }
    return result;
}

Result opBxor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(num1 ^ num2), NumberType::Integer};
    }
    return result;
}


// TODO: Replace this entire function with tgamma so it can return doubles correctly.
int factorial(int n) {
    int factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    return factorial;
}

Result opFactorial(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        if (const Number *dnum = std::get_if<Number>(&values.top().m_num)) {
            values.pop();
            result.num = std::tgamma(1 + (dnum->getRawDouble()));
        }
    }
    return result;
}

Result opChoose(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Number num1 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        Number num2 = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        result.num = factorial(num2.getRawDouble()) /
                     (factorial(num1.getRawDouble()) * factorial(num2.getRawDouble() - num1.getRawDouble()));
    }
    return result;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

Result opGCD(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(gcd(num1, num2)), NumberType::Integer};
    }
    return result;
}

Result opLCM(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        int num2 = static_cast<int>(std::get_if<Number>(&values.top().m_num)->getRawDouble());
        values.pop();
        result.num = {static_cast<double>(((num1 * num2) / gcd(num1, num2))), NumberType::Integer};
    }
    return result;
}

Result opLn(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Number num = *std::get_if<Number>(&values.top().m_num);
        values.pop();
        result.num = log(num.getRawDouble());
    }
    return result;
}

Result opLog(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    double num = 0;
    double base = 0;
    if (values.size() >= 2) {
        num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        base = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
    } else if (!values.empty()) {
        num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        base = 10.0;
    }
    result.num = log(num) / log(base);
    return result;
}

Result opTan(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = std::tan(num);
        std::cout << "**NOTE** Inputs to the tab function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCot(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = 1 / std::tan(num);
        std::cout << "**NOTE** Inputs to the cot function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opSec(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = 1 / std::cos(num);
        std::cout << "**NOTE** Inputs to the sec function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCsc(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = 1 / std::sin(num);
        std::cout << "**NOTE** Inputs to the csc function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArcsin(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = std::asin(num);
        std::cout << "**NOTE** Inputs to the arcsin function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArccos(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = std::acos(num);
        std::cout << "**NOTE** Inputs to the arcos function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArctan(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = std::get_if<Number>(&values.top().m_num)->getRawDouble();
        values.pop();
        result.num = std::atan(num);
        std::cout << "**NOTE** Inputs to the arctan function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opDot(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        result.num = std::visit(overload{
                [](Vector &v1, Vector &v2) -> Value {
                    return v1.dot(v2);
                },
                [&result](auto, auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num1.m_num, num2.m_num);
    }
    return result;
}

Result opCross(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        result.num = std::visit(overload{
                [&result](Vector &v1, Vector &v2) -> Value {
                    if (v1.size() == 3 && v2.size() == 3) {
                        return v1.cross(v2);
                    } else {
                        result.error = "Cross product only works for 3 dimensional vectors.";
                        return 0;
                    }

                },
                [&result](auto, auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num1.m_num, num2.m_num);
    }
    return result;
}

Result opMag(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [](Vector &v1) -> Value {
                    return v1.magnitude();
                },
                [&result](auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}

Result opNorm(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [](Vector &v1) -> Value {
                    return v1.normalize();
                },
                [&result](auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}

// TODO: Uninplemented, return the type of the value
Result opType(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [&result](auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}

Result opSum(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.num = std::visit(overload{
                [](Set &set) -> Value {
                    Number sum = Number(0, NumberType::Integer);
                    for (auto &num: set) {
                        sum += num;
                    }
                    return sum;
                },
                [](Vector &vec) -> Value {
                    Number sum = Number(0, NumberType::Integer);
                    for (auto &num: vec) {
                        sum += num;
                    }
                    return sum;
                },
                [&result](auto) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num.m_num);
    }
    return result;
}




//double derivative(const std::string &expression) {
//    for (int i = 0; i < expression.length(); i++) {
//        char token = expression[i];
//        if (token == ' ') {
//            continue;
//        } else if (token == 'x') {
//            if (i > 0) {
//                std::cout << "Coeffecient: " << expression[i - 1] << std::endl;
//            }
//            std::string var;
//            while (i < expression.length() && expression[i] != '^') {
//                var.push_back(expression[i++]);
//            }
//            i++;
//            std::cout << var << std::endl;
//            std::cout << "Exponent: " << expression[i] << std::endl;
//        }
//    }
//
//
//    return 0;
//}