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
    std::string error;
//    bool error;
//    OutputType type;
} Result;
const static Result DEFAULT_RESULT = {0, ""};


//typedef std::variant<int, double, std::vector<double>> Value;

typedef struct Op {
//    std::vector<int> validValueTypes;
    int precedence;
    int num_params;
    std::string token;
    std::vector<int> validValueTypes;
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

//double derivative(const std::string &expression);

const static std::unordered_map<std::string, Op> operations = {
        {"(",      {0, -1, "(",      {NONE},                               noOp}},
        {")",      {0, -1, ")",      {NONE},                               noOp}},
        {"[",      {0, -1, "[",      {NONE},                               noOp}},
        {"]",      {0, -1, "]",      {NONE},                               noOp}},
        {"{",      {0, -1, "{",      {NONE},                               noOp}},
        {"}",      {0, -1, "}",      {NONE},                               noOp}},
        {",",      {0, -1, ",",      {NONE},                               noOp}},
        {"|",      {0, 0,  "|",      {INTEGER, INTEGER},                   opBor}},
        {"&",      {0, 1,  "&",      {INTEGER, INTEGER},                   opBand}},
        {"+",      {0, 2,  "+",      {INTEGER | DOUBLE, INTEGER | DOUBLE}, opAdd}},
        {"-",      {0, 2,  "-",      {INTEGER | DOUBLE, INTEGER | DOUBLE}, opSub}},
        {"*",      {0, 3,  "*",      {INTEGER | DOUBLE, INTEGER | DOUBLE}, opMul}},
        {"/",      {0, 3,  "/",      {INTEGER | DOUBLE, INTEGER | DOUBLE}, opDiv}},
        {"%",      {0, 3,  "%",      {INTEGER, INTEGER},                   opMod}},
        {"^",      {0, 4,  "^",      {INTEGER | DOUBLE, INTEGER | DOUBLE}, opExp}},
        {"!",      {0, 4,  "!",      {INTEGER | DOUBLE},                   opFactorial}},
        {"sqrt",   {1, 4,  "sqrt",   {INTEGER | DOUBLE},                   opSqrt}},
        {"sin",    {1, 4,  "sin",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opSin}},
        {"cos",    {1, 4,  "cos",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opCos}},
        {"tan",    {1, 4,  "tan",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opTan}},
        {"cot",    {1, 4,  "cot",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opCot}},
        {"sec",    {1, 4,  "sec",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opSec}},
        {"csc",    {1, 4,  "csc",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opCsc}},
        {"arcsin", {1, 4,  "arcsin", {INTEGER | DOUBLE, INTEGER | DOUBLE}, opArcsin}},
        {"arccos", {1, 4,  "arccos", {INTEGER | DOUBLE, INTEGER | DOUBLE}, opArccos}},
        {"arctan", {1, 4,  "arctan", {INTEGER | DOUBLE, INTEGER | DOUBLE}, opArctan}},
        {"ln",     {1, 4,  "ln",     {INTEGER | DOUBLE, INTEGER | DOUBLE}, opLn}},         // ln(y) or log_e(y)
        {"log",    {1, 4,  "log",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opLog}},      // log_10(y)
        {"logb",   {2, 4,  "logb",   {INTEGER | DOUBLE, INTEGER | DOUBLE}, opLog}},    // log_x(y)
        {"gcd",    {2, 4,  "gcd",    {INTEGER, INTEGER},                   opGCD}},      // Greatest Common Divisor
        {"lcm",    {2, 4,  "lcm",    {INTEGER, INTEGER},                   opLCM}},      // Least Common Multiple
        {"bxor",   {2, 4,  "bxor",   {INTEGER, INTEGER},                   opBxor}},   // bxor(a, b) treated as (a ^ b)
        {"bor",    {2, 4,  "bor",    {INTEGER, INTEGER},                   opBor}},      // bor(a, b) treated as (a | b)
        {"band",   {2, 4,  "band",   {INTEGER, INTEGER},                   opBand}},   // band(a, b) treated as (a & b)
        {"mod",    {2, 4,  "mod",    {INTEGER, INTEGER},                   opMod}},      // mod(a, b) treated as (a % b)
        {"exp",    {2, 4,  "exp",    {INTEGER | DOUBLE, INTEGER | DOUBLE}, opExp}},
        {"choose", {2, 4,  "choose", {INTEGER | DOUBLE, INTEGER | DOUBLE}, opChoose}}
};

const static std::unordered_map<std::string, double> constants = {
        {"e",  std::exp(1.0)},
        {"pi", 2 * std::acos(0.0)},

};


#endif
