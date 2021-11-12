#include "Operations.h"


Result noOp(std::stack<Op> &ops, std::stack<Value> &values) {
    ops.pop();
    Result result = DEFAULT_RESULT;
//    result.error = false;
    return result;
}

Value addToSet(const double &a, std::vector<double> &b) {
    if (std::find(b.begin(), b.end(), a) == b.end()) {
        std::reverse(b.begin(), b.end());
        b.push_back(a);
        std::reverse(b.begin(), b.end());
    }
    return {b, SET};
}

Value subtractFromSet(const double &a, std::vector<double> &b) {
    auto it = std::find(b.begin(), b.end(), a);
    if (it != b.end()) {
        b.erase(it);
    }
    return {b, SET};
}

/**
 * Parameters must be vectors of the same size!
 * @param v1
 * @param v2
 * @return
 */
Value addVectors(std::vector<double> &v1, std::vector<double> &v2) {
    size_t size = v1.size();
    std::vector<double> result(size);
    for (int i = 0; i < size; i++) {
        result.at(i) = v2.at(i) + v1.at(i);
    }
    return {result, VECTOR};
}

Value subtractVectors(std::vector<double> &v1, std::vector<double> &v2) {
    size_t size = v1.size();
    std::vector<double> result(size);
    for (int i = 0; i < size; i++) {
        result.at(i) = v2.at(i) - v1.at(i);
    }
    return {result, VECTOR};
}


Result opAdd(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        Value num2 = values.top();
        values.pop();

        result.num = std::visit(overload{
                [](double &a, double &b) -> Value { return a + b; },
                [](Vector &a, Vector &b) -> Value { return a + b; },
                [](Set &a, Set &b) -> Value { return a + b; },
                [&result](auto &a, auto &b) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num1.num, num2.num);
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
                [](double &a, double &b) -> Value { return b - a; },
                [](Vector &a, Vector &b) -> Value { return b - a; },
                [](Set &a, Set &b) -> Value { return b - a; },
                [&result](auto &a, auto &b) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num1.num, num2.num);
    } else if (!values.empty()) {
        // TODO: Remove this entirely or find a reason for keeping it
//        Value num = values.top();
//        values.pop();
//        result.num = std::visit(overload{
//                [](int &n) -> Value { return -1 * n; },
//                [](double &n) -> Value { return -1 * n; },
//                [&num](std::vector<double> &n) -> Value {
//                    std::vector<double> result;
//                    for (auto &val: n) {
//                        result.push_back(-1 * val);
//                    }
//                    return {result, num.type};
//                },
//        }, num.num);
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
                [](double &a, double &b) -> Value { return b * a; },
                [](double &a, Vector &b) -> Value { return b.scalarMul(a); },
                [](double &a, Set &b) -> Value { return b.scalarMul(a); },
                [](Vector &a, double &b) -> Value { return a.scalarMul(b); },
                [](Vector &a, Vector &b) -> Value { return a.dot(b); },
                [](Set &a, double &b) -> Value { return a.scalarMul(b); },
                [](Set &a, Set &b) -> Value { return a.cartesianProduct(b); },
                [&result](auto &a, auto &b) -> Value {
                    result.error = "Unsupported opperation";
                    return 0;
                }
        }, num1.num, num2.num);

    }
    return result;
}

Result opDiv(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top().num);
        values.pop();
        double num2 = *std::get_if<double>(&values.top().num);
        values.pop();
        if (num1 == 0) {
            result.error = "Error, division by zero.";
            return result;
        }
        result.num = num2 / num1;
    }
    return result;
}

Result opMod(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    std::string token = ops.top().token;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = num2 % num1;
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
        double num1 = *std::get_if<double>(&values.top().num);
        values.pop();
        double num2 = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = pow(num2, num1);
    }
    return result;
}

Result opSqrt(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = sqrt(num);
    }
    return result;
}

Result opSin(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = sin(num);
        std::cout << "**NOTE** Inputs to the sin function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCos(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = cos(num);
    }
    return result;
}

Result opBand(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = num1 & num2;
    }
    return result;
}

Result opBor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = num1 | num2;
    }
    return result;
}

Result opBxor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = num1 ^ num2;
    }
    return result;
}

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
        if (const double *dnum = std::get_if<double>(&values.top().num)) {
            values.pop();
            result.num = std::tgamma(1 + (*dnum));
        }
    }
    return result;
}

Result opChoose(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top().num);
        values.pop();
        double num2 = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = factorial(num2) / (factorial(num1) * factorial(num2 - num1));
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
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = gcd(num1, num2);
    }
    return result;
}

Result opLCM(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top().num));
        values.pop();
        result.num = ((num1 * num2) / gcd(num1, num2));
    }
    return result;
}

Result opLn(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = log(num);
    }
    return result;
}

Result opLog(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    double num = 0;
    double base = 0;
    if (values.size() >= 2) {
        num = *std::get_if<double>(&values.top().num);
        values.pop();
        base = *std::get_if<double>(&values.top().num);
        values.pop();
    } else if (!values.empty()) {
        num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
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
        double num = *std::get_if<double>(&values.top().num);
        values.pop();
        result.num = std::atan(num);
        std::cout << "**NOTE** Inputs to the arctan function interpreted as RADIANS" << std::endl;
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