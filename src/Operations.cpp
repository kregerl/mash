#include "Operations.h"

Value noOp(std::stack<Op> &ops, std::stack<Value> &values) {
    std::cout << ops.top().token << std::endl;

    ops.pop();
    Value result;
//    result.error = false;
    result.setError("Cannot apply null operation to values");
    return result;
}

Value opAdd(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }

        result.setNum(std::visit(overload{
                [](Number &a, Number &b) -> Value { return {a + b}; },
                [](Vector &a, Vector &b) -> Value { return a + b; },
                [](Set &a, Set &b) -> Value { return a + b; },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.setError("Unsupported operation: Cannot add type of " +
                                    typeStrings[static_cast<int>(num1.getType())] + " to " +
                                    typeStrings[static_cast<int>(num2.getType())] + ".");
                    return 0;
                }
        }, num1.getNum(), num2.getNum()));
    }
    return result;
}


Value opSub(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }

        result.setNum(std::visit(overload{
                [](Number &a, Number &b) -> Value { return b - a; },
                [](Vector &a, Vector &b) -> Value { return b - a; },
                [](Set &a, Set &b) -> Value { return b - a; },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.setError("Unsupported operation: Cannot subtract type of " +
                                    typeStrings[static_cast<int>(num1.getType())] + " to " +
                                    typeStrings[static_cast<int>(num2.getType())] + ".");
                    return 0;
                }
        }, num1.getNum(), num2.getNum()));
    } else if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }
        result.setNum(std::visit(overload{
                [](Number &a) -> Value { return a * Number(-1); },
                [](Vector &a) -> Value { return a.scalarMul(-1); },
                [](Set &a) -> Value { return a.scalarMul(-1); },
                [&result](auto &a) -> Value {
                    result.setError("Unsupported operation: This should never happen.");
                    return 0;
                }
        }, num.getNum()));
    }
    return result;
}

Value opMul(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }

        result.setNum(std::visit(overload{
                [](Number &a, Number &b) -> Value { return b * a; },
                [](Number &a, Vector &b) -> Value { return b.scalarMul(a.getRawDouble()); },
                [](Number &a, Set &b) -> Value { return b.scalarMul(a.getRawDouble()); },
                [](Vector &a, Number &b) -> Value { return a.scalarMul(b.getRawDouble()); },
                [](Vector &a, Vector &b) -> Value { return a.dot(b); },
                [](Set &a, Number &b) -> Value { return a.scalarMul(b.getRawDouble()); },
                [](Set &a, Set &b) -> Value { return a.cartesianProduct(b); },
                [&result, &num1, &num2](auto &a, auto &b) -> Value {
                    result.setError("Unsupported operation: Cannot multiply type of " +
                                    typeStrings[static_cast<int>(num1.getType())] + " to " +
                                    typeStrings[static_cast<int>(num2.getType())] + ".");
                    return 0;
                }
        }, num1.getNum(), num2.getNum()));

    }
    return result;
}

Value opDiv(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        Number num1 = *std::get_if<Number>(&v1.getNum());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        Number num2 = *std::get_if<Number>(&v2.getNum());
        if (num1.getRawDouble() == 0) {
            result.setError("Error, division by zero.");
            return result;
        }
        result.setNum(num2.getRawDouble() / num1.getRawDouble());
    }
    return result;
}

Value opMod(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    Op op = ops.top();
    std::string token = ops.top().token;
    ops.pop();

    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(num2 % num1), NumberType::Integer});
    }
//    else if (token == "mod") {
//        std::cout << "Mod: `mod(a, b)` returns the result of `a mod b`. Can also be represented as `(a % b)`" << std::endl;
//        result.error = false;
//    }
    return result;
}

Value opExp(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        Number num1 = *std::get_if<Number>(&v1.getNum());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        Number num2 = *std::get_if<Number>(&v2.getNum());
        result.setNum({pow(num2.getRawDouble(), num1.getRawDouble()), num1.opResultType(num2)});
    }
    return result;
}

Value opSqrt(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }
        result.setNum(std::visit(overload{
                [](Number &a) -> Value { return sqrt(a.getRawDouble()); },
                [](Vector &a) -> Value { return a.sqrt(); },
                [&result, &num](auto &a) -> Value {
                    result.setError("Unsupported operation: Cannot take the square root of a " +
                                    typeStrings[static_cast<int>(num.getType())] + ".");
                    return 0;
                }
        }, num.getNum()));
    }
    return result;
}

Value opSin(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        Number num = *std::get_if<Number>(&top.getNum());

        double res = sin(num.getRawDouble());
        // TODO: Check if number is so small that it is essentially 0 for all values.
        result.setNum(res < 1e-8 ? 0 : res);
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opCos(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        Number num = *std::get_if<Number>(&top.getNum());
        result.setNum(cos(num.getRawDouble()));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opBand(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(num1 & num2), NumberType::Integer});
    }
    return result;
}

Value opBor(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(num1 | num2), NumberType::Integer});
    }
    return result;
}

Value opBxor(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(num1 ^ num2), NumberType::Integer});
    }
    return result;
}


Number factorial(const Number &n) {
    return Number(std::tgamma(1 + (n.getRawDouble())));
}

Value opFactorial(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        if (const Number *dnum = std::get_if<Number>(&top.getNum())) {
            result.setNum(factorial(*dnum));
        }
    }
    return result;
}

Number combination(const Number &a, const Number &b) {
    return Number(factorial(a) /
                  (factorial(b) * factorial(a - b)));
}

Value opChoose(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        Number num1 = *std::get_if<Number>(&v1.getNum());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        Number num2 = *std::get_if<Number>(&v2.getNum());
        result.setNum(combination(num2, num1));
    }
    return result;
}

int gcd(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}

Value opGCD(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(gcd(num1, num2)), NumberType::Integer});
    }
    return result;
}

Value opLCM(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        int num1 = static_cast<int>(std::get_if<Number>(&v1.getNum())->getRawDouble());
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        int num2 = static_cast<int>(std::get_if<Number>(&v2.getNum())->getRawDouble());
        result.setNum({static_cast<double>(((num1 * num2) / gcd(num1, num2))), NumberType::Integer});
    }
    return result;
}

Value opLn(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        Number num = *std::get_if<Number>(&top.getNum());
        result.setNum(log(num.getRawDouble()));
    }
    return result;
}

Value opLog(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    double num = 0;
    double base = 0;
    if (values.size() >= 2) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        num = std::get_if<Number>(&v1.getNum())->getRawDouble();
        Value v2 = values.top();
        values.pop();
        if (v2.getError()) {
            return v2;
        }
        base = std::get_if<Number>(&v2.getNum())->getRawDouble();
    } else if (!values.empty()) {
        Value v1 = values.top();
        values.pop();
        if (v1.getError()) {
            return v1;
        }
        num = std::get_if<Number>(&v1.getNum())->getRawDouble();
        base = 10.0;
    }
    result.setNum(log(num) / log(base));
    return result;
}

Value opTan(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(std::tan(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opCot(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(1 / std::tan(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opSec(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(1 / std::cos(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opCsc(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(1 / std::sin(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");

    }
    return result;
}

Value opArcsin(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(1 / std::sin(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");

    }
    return result;
}

Value opArccos(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(std::acos(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");

    }
    return result;
}

Value opArctan(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value top = values.top();
        values.pop();
        if (top.getError()) {
            return top;
        }
        double num = std::get_if<Number>(&top.getNum())->getRawDouble();
        result.setNum(std::atan(num));
        result.setMessage("**NOTE** Inputs to the sin function interpreted as RADIANS");
    }
    return result;
}

Value opDot(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }

        result.setNum(std::visit(overload{
                [](Vector &v1, Vector &v2) -> Value {
                    return v1.dot(v2);
                },
                [&result](auto, auto) -> Value {
                    result.setError("Unsupported opperation");
                    return 0;
                }
        }, num1.getNum(), num2.getNum()));
    }
    return result;
}

Value opCross(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }

        result.setNum(std::visit(overload{
                [&result](Vector &v1, Vector &v2) -> Value {
                    if (v1.size() == 3 && v2.size() == 3) {
                        return v1.cross(v2);
                    } else {
                        result.setError("Cross product only works for 3 dimensional vectors.");
                        return 0;
                    }

                },
                [&result](auto, auto) -> Value {
                    result.setError("Unsupported opperation");
                    return 0;
                }
        }, num1.getNum(), num2.getNum()));
    }
    return result;
}

Value opMag(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }
        result.setNum(std::visit(overload{
                [](Vector &v1) -> Value {
                    return v1.magnitude();
                },
                [&result](auto) -> Value {
                    result.setError("Unsupported opperation");
                    return 0;
                }
        }, num.getNum()));
    }
    return result;
}

Value opNorm(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }
        result.setNum(std::visit(overload{
                [](Vector &v1) -> Value {
                    return v1.normalize();
                },
                [&result](auto) -> Value {
                    result.setError("Unsupported opperation");
                    return 0;
                }
        }, num.getNum()));
    }
    return result;
}

// TODO: Uninplemented, return the type of the value
Value opType(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        result.setNum(std::visit(overload{
                [&result, &num](auto) -> Value {
                    result.setMessage(typeStrings[static_cast<int>(num.getType())]);
                    return num;
                }
        }, num.getNum()));
    }
    return result;
}

Value opSum(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }
        result.setNum(std::visit(overload{
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
                    result.setError("Unsupported opperation");
                    return 0;
                }
        }, num.getNum()));
    }
    return result;
}

Value opMin(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }

        result.setNum(std::visit(overload{
                [](Number &num) -> Value {
                    return num;
                },
                [](Set &set) -> Value {
                    return set.min();
                },
                [](Vector &vec) -> Value {
                    return vec.min();
                }
        }, num.getNum()));

    }
    return result;
}

Value opMax(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    if (!values.empty()) {
        Value num = values.top();
        values.pop();
        if (num.getError()) {
            return num;
        }

        result.setNum(std::visit(overload{
                [](Number &num) -> Value {
                    return num;
                },
                [](Set &set) -> Value {
                    return set.max();
                },
                [](Vector &vec) -> Value {
                    return vec.max();
                }
        }, num.getNum()));

    }
    return result;
}


Number binomialDensity(const Number &x, const Number &size, const Number &prob) {
    return combination(size, x) * std::pow(prob.getRawDouble(), x.getRawDouble()) *
           std::pow(1 - prob.getRawDouble(), size.getRawDouble() - x.getRawDouble());
}

Value opDbinom(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dbinom on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number prob = *std::get_if<Number>(&num1.getNum());
        Number size = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(binomialDensity(x, size, prob));

    }
    return result;
}

Number binomialDistribution(const Number &x, const Number &size, const Number &prob) {
    auto sum = Number(0);
    for (int i = 0; i <= x.getRawDouble(); i++) {
        sum += binomialDensity(Number(i), size, prob);
    }
    return sum;
}

Value opPbinom(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support pbinom on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number prob = *std::get_if<Number>(&num1.getNum());
        Number size = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(binomialDistribution(x, size, prob));
    }
    return result;
}

Number exponentialDensity(const Number &x, const Number &lambda) {
    return lambda * std::pow(constants.at("e"), (lambda * -1.0 * x).getRawDouble());
}

Value opDexp(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dexp on sets for the first argument (`x`).
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Number lambda = *std::get_if<Number>(&num1.getNum());
        Number x = *std::get_if<Number>(&num2.getNum());
        result.setNum(exponentialDensity(x, lambda));
    }
    return result;
}

Number exponentialDistribution(const Number &x, const Number &lambda) {
    return Number(1.0 - std::pow(constants.at("e"), (x * lambda * -1.0).getRawDouble()));
}

Value opPexp(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support pexp on sets for the first argument (`x`).
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Number lambda = *std::get_if<Number>(&num1.getNum());
        Number x = *std::get_if<Number>(&num2.getNum());
        result.setNum(exponentialDistribution(x, lambda));
    }
    return result;
}

Number uniformDensity(const Number &min, const Number &max) {
    return Number(1 / (max - min).getRawDouble());
}

Value opDunif(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dunif on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number max = *std::get_if<Number>(&num1.getNum());
        Number min = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(uniformDensity(min, max));
    }
    return result;
}

Number uniformDistribution(const Number &x, const Number &min, const Number &max) {
    return x * uniformDensity(min, max);
}

Value opPunif(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dunif on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number max = *std::get_if<Number>(&num1.getNum());
        Number min = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(uniformDistribution(x, min, max));
    }
    return result;
}

Number poissonDensity(const Number &x, const Number &lambda) {
    return Number((std::pow(constants.at("e"), (lambda.getRawDouble() * -1.0)) *
                   std::pow(lambda.getRawDouble(), x.getRawDouble())) / factorial(x).getRawDouble());
}

Value opDpois(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dpois on sets for the first argument (`x`).
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }


        Number lambda = *std::get_if<Number>(&num1.getNum());
        Number x = *std::get_if<Number>(&num2.getNum());
        result.setNum(poissonDensity(x, lambda));
    }
    return result;
}

Number poissonDistribution(const Number &x, const Number &lambda) {
    auto sum = Number(0);
    for (int i = 0; i <= x.getRawDouble(); i++) {
        sum += poissonDensity(Number(i), lambda);
    }
    return sum;
}

Value opPpois(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dpois on sets for the first argument (`x`).
    if (values.size() >= 2) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }


        Number lambda = *std::get_if<Number>(&num1.getNum());
        Number x = *std::get_if<Number>(&num2.getNum());
        result.setNum(poissonDistribution(x, lambda));
    }
    return result;
}

Number hypergeometricDensity(const Number &x, const Number &m1, const Number &m2, const Number &n) {
    return (combination(m1, x) * combination(m2, n - x)) / combination(m1 + m2, n);
}

Value opDhyper(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dhyper on sets for the first argument (`x`).
    if (values.size() >= 4) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }
        Value num4 = values.top();
        values.pop();
        if (num4.getError()) {
            return num4;
        }

        Number n = *std::get_if<Number>(&num1.getNum());
        Number m2 = *std::get_if<Number>(&num2.getNum());
        Number m1 = *std::get_if<Number>(&num3.getNum());
        Number x = *std::get_if<Number>(&num4.getNum());
        result.setNum(hypergeometricDensity(x, m1, m2, n));
    }
    return result;
}

Number hypergeometricDistribution(const Number &x, const Number &m1, const Number &m2, const Number &n) {
    auto sum = Number(0);
    for (int i = 0; i <= x.getRawDouble(); i++) {
        sum += hypergeometricDensity(Number(i), m1, m2, n);
    }
    return sum;
}

Value opPhyper(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support phyper on sets for the first argument (`x`).
    if (values.size() >= 4) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }
        Value num4 = values.top();
        values.pop();
        if (num4.getError()) {
            return num4;
        }

        Number n = *std::get_if<Number>(&num1.getNum());
        Number m2 = *std::get_if<Number>(&num2.getNum());
        Number m1 = *std::get_if<Number>(&num3.getNum());
        Number x = *std::get_if<Number>(&num4.getNum());
        result.setNum(hypergeometricDistribution(x, m1, m2, n));
    }
    return result;
}

Number normalDensity(const Number &x, const Number &mean, const Number &sd) {
    return Number((1 / (sd * std::sqrt(2 * constants.at("pi"))).getRawDouble()) *
                  std::pow(constants.at("e"),
                           ((-1.0 / 2.0) * std::pow((x - mean).getRawDouble() / sd.getRawDouble(), 2.0))));


}

Value opDnorm(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dunif on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number sd = *std::get_if<Number>(&num1.getNum());
        Number mean = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(normalDensity(x, mean, sd));
    }
    return result;
}

Number normalDistribtion(const Number &x, const Number &mean, const Number &sd) {
    return Number(std::pow(constants.at("e"),
                           std::pow(((x * -1.0) - mean).getRawDouble(), 2.0) / (2 * std::pow(sd.getRawDouble(), 2.0))) /
                  (sd.getRawDouble() * std::sqrt(2 * constants.at("pi"))));
}

Value opPnorm(std::stack<Op> &ops, std::stack<Value> &values) {
    Value result;
    ops.pop();
    // TODO: Support dunif on sets for the first argument (`x`).
    if (values.size() >= 3) {
        Value num1 = values.top();
        values.pop();
        if (num1.getError()) {
            return num1;
        }
        Value num2 = values.top();
        values.pop();
        if (num2.getError()) {
            return num2;
        }
        Value num3 = values.top();
        values.pop();
        if (num3.getError()) {
            return num3;
        }

        Number sd = *std::get_if<Number>(&num1.getNum());
        Number mean = *std::get_if<Number>(&num2.getNum());
        Number x = *std::get_if<Number>(&num3.getNum());
        result.setNum(normalDistribtion(x, mean, sd));
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