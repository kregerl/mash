#ifndef MASH_OPERATIONS_H
#define MASH_OPERATIONS_H
#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include <unordered_map>

/**
 * precedence
 * - Bracket and seperator characters -1
 * - Add / Subtract 0
 * - Multiply / Divide / Mod 1
 * - Exponent / sqrt 2
 */

//const static std::string OutputFormats[3] = {"%.2f\n", "%x\n", "%.2f\n"};
//enum class OutputType {
//    Decimal = 0, Hex = 1, Bin = 2
//};

// Add a string for when an operation errors.
typedef struct {
    double num;
    bool error;
//    OutputType type;
} Result;
const static Result DEFAULT_RESULT = {0, true};

typedef struct Op {
    int num_params;
    int precedence;
    std::string token;
    std::function<Result(std::stack<struct Op>&, std::stack<double>&)> func;
} Op;

Result noOp(std::stack<Op> &ops, std::stack<double> &values);
Result opAdd(std::stack<Op> &ops, std::stack<double> &values);
Result opSub(std::stack<Op> &ops, std::stack<double> &values);
Result opMul(std::stack<Op> &ops, std::stack<double> &values);
Result opDiv(std::stack<Op> &ops, std::stack<double> &values);
Result opMod(std::stack<Op> &ops, std::stack<double> &values);
Result opExp(std::stack<Op> &ops, std::stack<double> &values);
Result opSqrt(std::stack<Op> &ops, std::stack<double> &values);
Result opSin(std::stack<Op> &ops, std::stack<double> &values);
Result opCos(std::stack<Op> &ops, std::stack<double> &values);
Result opBand(std::stack<Op> &ops, std::stack<double> &values);
Result opBor(std::stack<Op> &ops, std::stack<double> &values);
Result opBxor(std::stack<Op> &ops, std::stack<double> &values);
long factorial(int n);
Result opFactorial(std::stack<Op> &ops, std::stack<double> &values);
Result opChoose(std::stack<Op> &ops, std::stack<double> &values);


const static std::unordered_map<std::string, Op> operations({
    {"(", {0, -1, "(", noOp}},
    {")", {0, -1, ")", noOp}},
    {",", {0, -1, ",", noOp}},
    {"|", {0, 0, "|", opBor}},
    {"&", {0, 1, "&", opBand}},
    {"+", {0, 2, "+", opAdd}},
    {"-", {0, 2, "-", opSub}},
    {"*", {0, 3, "*", opMul}},
    {"/", {0, 3, "/", opDiv}},
    {"%", {0, 3, "%", opMod}},
    {"^", {0, 4, "^", opExp}},
    {"!", {0, 4, "!", opFactorial}},
    {"sqrt", {1, 4, "sqrt", opSqrt}},
    {"sin", {1, 4, "sin", opSin}},
    {"cos", {1, 4, "cos", opCos}},
    {"bxor", {2, 4, "bxor", opBxor}},   // bxor(a, b) treated as (a ^ b)
    {"bor", {2, 4, "bor", opBor}},      // bor(a, b) treated as (a | b)
    {"band", {2, 4, "band", opBand}},   // band(a, b) treated as (a & b)
    {"mod", {2, 4, "mod", opMod}},      // mod(a, b) treated as (a % b)
    {"exp", {2, 4, "exp", opExp}},      // exp(a, b) treated as (a ** b)
    {"choose", {2, 4, "choose", opChoose}},   // choose(a, b) treated as (a choose b)

});

const static std::unordered_map<std::string, double> constants ({
    {"e", 2.71828182845904523536},
    {"pi", 3.14159265358979323846},
});


#endif
