#ifndef MASH_OPERATIONS_H
#define MASH_OPERATIONS_H

#include <string>
#include <iostream>
#include <stack>
#include <functional>
#include <unordered_map>
#include <cmath>
#include "Value.h"



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
    Value num;
    std::optional<std::string> error;
//    bool error;
//    OutputType type;
} Result;
const static Result DEFAULT_RESULT = {0};


//typedef std::variant<int, double, std::vector<double>> Value;

typedef struct Op {
    int num_params;
    int precedence;
    std::string token;
    std::vector<NumberType> validValueTypes;
    std::function<Result(std::stack<struct Op> &, std::stack<Value> &)> func;
} Op;

Result noOp(std::stack<Op> &ops, std::stack<Value> &values);

Result opAdd(std::stack<Op> &ops, std::stack<Value> &values);

Value addToSet(const double &a, std::vector<double> &b);

Value subtractFromSet(const double &a, std::vector<double> &b);

Value addVectors(std::vector<double> &v1, std::vector<double> &v2);

Value subtractVectors(std::vector<double> &v1, std::vector<double> &v2);

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

int factorial(int n);

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

Result opDot(std::stack<Op> &ops, std::stack<Value> &values);

Result opCross(std::stack<Op> &ops, std::stack<Value> &values);

Result opMag(std::stack<Op> &ops, std::stack<Value> &values);

Result opNorm(std::stack<Op> &ops, std::stack<Value> &values);

//double derivative(const std::string &expression);

const static std::unordered_map<std::string, Op> operations = {
        {"(",      {0, -1, "(",      {NumberType::None},                                         noOp}},
        {")",      {0, -1, ")",      {NumberType::None},                                         noOp}},
        {"[",      {0, -1, "[",      {NumberType::None},                                         noOp}},
        {"]",      {0, -1, "]",      {NumberType::None},                                         noOp}},
        {"{",      {0, -1, "{",      {NumberType::None},                                         noOp}},
        {"}",      {0, -1, "}",      {NumberType::None},                                         noOp}},
        {",",      {0, -1, ",",      {NumberType::None},                                         noOp}},
        {"|",      {0, 0,  "|",      {NumberType::Integer},                                      opBor}},
        {"&",      {0, 1,  "&",      {NumberType::Integer},                                      opBand}},
        {"+",      {0, 2,  "+",      {NumberType::VectorOrSetOrIntegerOrDouble},                 opAdd}},
        {"-",      {0, 2,  "-",      {NumberType::VectorOrSetOrIntegerOrDouble},                 opSub}},
        {"*",      {0, 3,  "*",      {NumberType::VectorOrSetOrIntegerOrDouble},                 opMul}},
        {"/",      {0, 3,  "/",      {NumberType::IntegerOrDouble},                              opDiv}},
        {"%",      {0, 3,  "%",      {NumberType::Integer},                                      opMod}},
        {"^",      {0, 4,  "^",      {NumberType::IntegerOrDouble},                              opExp}},
        {"!",      {0, 4,  "!",      {NumberType::IntegerOrDouble},                              opFactorial}},
        {"sqrt",   {1, 4,  "sqrt",   {NumberType::IntegerOrDouble},                              opSqrt}},
        {"sin",    {1, 4,  "sin",    {NumberType::IntegerOrDouble},                              opSin}},
        {"cos",    {1, 4,  "cos",    {NumberType::IntegerOrDouble},                              opCos}},
        {"tan",    {1, 4,  "tan",    {NumberType::IntegerOrDouble},                              opTan}},
        {"cot",    {1, 4,  "cot",    {NumberType::IntegerOrDouble},                              opCot}},
        {"sec",    {1, 4,  "sec",    {NumberType::IntegerOrDouble},                              opSec}},
        {"csc",    {1, 4,  "csc",    {NumberType::IntegerOrDouble},                              opCsc}},
        {"arcsin", {1, 4,  "arcsin", {NumberType::IntegerOrDouble},                              opArcsin}},
        {"arccos", {1, 4,  "arccos", {NumberType::IntegerOrDouble},                              opArccos}},
        {"arctan", {1, 4,  "arctan", {NumberType::IntegerOrDouble},                              opArctan}},
        {"ln",     {1, 4,  "ln",     {NumberType::IntegerOrDouble},                              opLn}},         // ln(y) or log_e(y)
        {"log",    {1, 4,  "log",    {NumberType::IntegerOrDouble},                              opLog}},      // log_10(y)
        {"mag",    {1, 4,  "mag",    {NumberType::Vector},                                       opMag}},      // log_10(y)
        {"norm",   {1, 4,  "norm",   {NumberType::Vector},                                       opNorm}},      // log_10(y)
        {"logb",   {2, 4,  "logb",   {NumberType::IntegerOrDouble, NumberType::IntegerOrDouble}, opLog}},    // log_x(y)
        {"gcd",    {2, 4,  "gcd",    {NumberType::Integer,         NumberType::Integer},         opGCD}},      // Greatest Common Divisor
        {"lcm",    {2, 4,  "lcm",    {NumberType::Integer,         NumberType::Integer},         opLCM}},      // Least Common Multiple
        {"bxor",   {2, 4,  "bxor",   {NumberType::Integer,         NumberType::Integer},         opBxor}},   // bxor(a, b) treated as (a ^ b)
        {"bor",    {2, 4,  "bor",    {NumberType::Integer,         NumberType::Integer},         opBor}},      // bor(a, b) treated as (a | b)
        {"band",   {2, 4,  "band",   {NumberType::Integer,         NumberType::Integer},         opBand}},   // band(a, b) treated as (a & b)
        {"mod",    {2, 4,  "mod",    {NumberType::Integer,         NumberType::Integer},         opMod}},      // mod(a, b) treated as (a % b)
        {"exp",    {2, 4,  "exp",    {NumberType::IntegerOrDouble, NumberType::IntegerOrDouble}, opExp}},
        {"choose", {2, 4,  "choose", {NumberType::IntegerOrDouble, NumberType::IntegerOrDouble}, opChoose}},
        {"dot",    {2, 4,  "dot",    {NumberType::Vector,          NumberType::Vector},          opDot}},
        {"cross",  {2, 4,  "cross",  {NumberType::Vector,          NumberType::Vector},          opCross}},
};

const static std::unordered_map<std::string, double> constants = {
        {"e",   std::exp(1.0)},
        {"pi",  2 * std::acos(0.0)},
        {"phi", ((1 + sqrt(5)) / 2)},

};


#endif
