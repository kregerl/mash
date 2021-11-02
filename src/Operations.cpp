#include "Operations.h"

Result noOp(std::stack<Op> &ops, std::stack<Value> &values) {
    ops.pop();
    Result result = DEFAULT_RESULT;
    result.error = false;
    return result;
}

Result opAdd(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
        values.pop();
        result.num = num1 + num2;
        result.error = false;
    }
    return result;
}

Result opSub(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 =*std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = num2 - num1;
    } else if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = -1 * num;
    }
    return result;
}

Result opMul(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
        values.pop();
        result.num = num1 * num2;
        result.error = false;
    }
    return result;
}

Result opDiv(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
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

Result opMod(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    std::string token = ops.top().token;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
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
        double num1 = *std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = pow(num2, num1);
    }
    return result;
}

Result opSqrt(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = sqrt(num);
    }
    return result;
}

Result opSin(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = sin(num);
        std::cout << "**NOTE** Inputs to the sin function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCos(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = cos(num);
    }
    return result;
}

Result opBand(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = num1 & num2;
    }
    return result;
}

Result opBor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = num1 | num2;
    }
    return result;
}

Result opBxor(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = num1 ^ num2;
    }
    return result;
}

long factorial(int n) {
    long factorial = 1;
    for (int i = 1; i <= n; i++) {
        factorial *= i;
    }
    return factorial;
}

Result opFactorial(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        // TODO: Allow this to work with decimal numbers, must be able to read decimal numbers first.
        int num = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = static_cast<double>(factorial(num));
    }
    return result;
}

Result opChoose(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        double num1 = *std::get_if<double>(&values.top());
        values.pop();
        double num2 = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
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
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = gcd(num1, num2);
    }
    return result;
}

Result opLCM(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (values.size() >= 2) {
        int num1 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        int num2 = static_cast<int>(*std::get_if<double>(&values.top()));
        values.pop();
        result.error = false;
        result.num = ((num1 * num2) / gcd(num1, num2));
    }
    return result;
}

Result opLn(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
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
        num = *std::get_if<double>(&values.top());
        values.pop();
        base = *std::get_if<double>(&values.top());
        values.pop();
    } else if (!values.empty()) {
        num = *std::get_if<double>(&values.top());
        values.pop();
        base = 10.0;
    }
    result.error = false;
    result.num = log(num) / log(base);
    return result;
}

Result opTan(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = std::tan(num);
        std::cout << "**NOTE** Inputs to the tab function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCot(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = 1 / std::tan(num);
        std::cout << "**NOTE** Inputs to the cot function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opSec(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = 1 / std::cos(num);
        std::cout << "**NOTE** Inputs to the sec function interpreted as RADIANS" << std::endl;
    }
    return result;
}

Result opCsc(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = 1 / std::sin(num);
        std::cout << "**NOTE** Inputs to the csc function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArcsin(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = std::asin(num);
        std::cout << "**NOTE** Inputs to the arcsin function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArccos(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
        result.num = std::acos(num);
        std::cout << "**NOTE** Inputs to the arcos function interpreted as RADIANS" << std::endl;

    }
    return result;
}

Result opArctan(std::stack<Op> &ops, std::stack<Value> &values) {
    Result result = DEFAULT_RESULT;
    ops.pop();
    if (!values.empty()) {
        double num = *std::get_if<double>(&values.top());
        values.pop();
        result.error = false;
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