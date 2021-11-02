#ifndef MASH_OPERATIONS_H
#define MASH_OPERATIONS_H

#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include <unordered_map>
#include <cmath>
#include <variant>

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

typedef std::variant<int, double, std::vector<double>> Value;

typedef struct Op {
    int num_params;
    int precedence;
    std::string token;
    std::function<Result(std::stack<struct Op> &, std::stack<Value> &)> func;
} Op;

Result noOp(std::stack<Op> &ops, std::stack<Value> &values);

Result opAdd(std::stack<Op> &ops, std::stack<Value> &values);

Result opSub(std::stack<Op> &ops, std::stack<Value> &values);

Result opMul(std::stack<Op> &ops, std::stack<Value> &values);

Result opDiv(std::stack<Op> &ops, std::stack<Value> &values);

Result opMod(std::stack<Op> &ops, std::stack<Value> &values);

Result opExp(std::stack<Op> &ops, std::stack<Value> &values);

Result opSqrt(std::stack<Op> &ops, std::stack<Value> &values);

Result opSin(std::stack<Op> &ops, std::stack<Value> &values);

Result opCos(std::stack<Op> &ops, std::stack<Value> &values);

Result opBand(std::stack<Op> &ops, std::stack<Value> &values);

Result opBor(std::stack<Op> &ops, std::stack<Value> &values);

Result opBxor(std::stack<Op> &ops, std::stack<Value> &values);

long factorial(int n);

Result opFactorial(std::stack<Op> &ops, std::stack<Value> &values);

Result opChoose(std::stack<Op> &ops, std::stack<Value> &values);

int gcd(int a, int b);

Result opGCD(std::stack<Op> &ops, std::stack<Value> &values);

Result opLCM(std::stack<Op> &ops, std::stack<Value> &values);

Result opLn(std::stack<Op> &ops, std::stack<Value> &values);

Result opLog(std::stack<Op> &ops, std::stack<Value> &values);

Result opTan(std::stack<Op> &ops, std::stack<Value> &values);

Result opCot(std::stack<Op> &ops, std::stack<Value> &values);

Result opSec(std::stack<Op> &ops, std::stack<Value> &values);

Result opCsc(std::stack<Op> &ops, std::stack<Value> &values);

Result opArcsin(std::stack<Op> &ops, std::stack<Value> &values);

Result opArccos(std::stack<Op> &ops, std::stack<Value> &values);

Result opArctan(std::stack<Op> &ops, std::stack<Value> &values);

//double derivative(const std::string &expression);

const static std::unordered_map<std::string, Op> operations = {
        {"(",      {0, -1, "(",      noOp}},
        {")",      {0, -1, ")",      noOp}},
        {"[",      {0, -1, "[",      noOp}},
        {"]",      {0, -1, "]",      noOp}},
        {"{",      {0, -1, "{",      noOp}},
        {"}",      {0, -1, "}",      noOp}},
        {",",      {0, -1, ",",      noOp}},
        {"|",      {0, 0,  "|",      opBor}},
        {"&",      {0, 1,  "&",      opBand}},
        {"+",      {0, 2,  "+",      opAdd}},
        {"-",      {0, 2,  "-",      opSub}},
        {"*",      {0, 3,  "*",      opMul}},
        {"/",      {0, 3,  "/",      opDiv}},
        {"%",      {0, 3,  "%",      opMod}},
        {"^",      {0, 4,  "^",      opExp}},
        {"!",      {0, 4,  "!",      opFactorial}},
        {"sqrt",   {1, 4,  "sqrt",   opSqrt}},
        {"sin",    {1, 4,  "sin",    opSin}},
        {"cos",    {1, 4,  "cos",    opCos}},
        {"tan",    {1, 4,  "tan",    opTan}},
        {"cot",    {1, 4,  "cot",    opCot}},
        {"sec",    {1, 4,  "sec",    opSec}},
        {"csc",    {1, 4,  "csc",    opCsc}},
        {"arcsin", {1, 4,  "arcsin", opArcsin}},
        {"arccos", {1, 4,  "arccos", opArccos}},
        {"arctan", {1, 4,  "arctan", opArctan}},
        {"ln",     {1, 4,  "ln",     opLn}},         // ln(y) or log_e(y)
        {"log",    {1, 4,  "log",    opLog}},      // log_10(y)
        {"logb",   {2, 4,  "logb",   opLog}},    // log_x(y)
        {"gcd",    {2, 4,  "gcd",    opGCD}},      // Greatest Common Divisor
        {"lcm",    {2, 4,  "lcm",    opLCM}},      // Least Common Multiple
        {"bxor",   {2, 4,  "bxor",   opBxor}},   // bxor(a, b) treated as (a ^ b)
        {"bor",    {2, 4,  "bor",    opBor}},      // bor(a, b) treated as (a | b)
        {"band",   {2, 4,  "band",   opBand}},   // band(a, b) treated as (a & b)
        {"mod",    {2, 4,  "mod",    opMod}},      // mod(a, b) treated as (a % b)
        {"exp",    {2, 4,  "exp",    opExp}},      // exp(a, b) treated as (a ** b)
        {"choose", {2, 4,  "choose", opChoose}},   // choose(a, b) treated as (a choose b)
};

const static std::unordered_map<std::string, double> constants = {
        {"e",  std::exp(1.0)},
        {"pi", 2 * std::acos(0.0)},

};


#endif
