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

// Add a string for when an operation errors.
//typedef struct {
//    Value num;
//    std::optional<std::string> error;
//} Result;

typedef struct Op {
    int num_params;
    int precedence;
    std::string token;
    std::function<Value(std::stack<struct Op> &, std::stack<Value> &)> func;
} Op;

Value noOp(std::stack<Op> &ops, std::stack<Value> &values);

Value opAdd(std::stack<Op> &ops, std::stack<Value> &values);

Value opSub(std::stack<Op> &ops, std::stack<Value> &values);

Value opMul(std::stack<Op> &ops, std::stack<Value> &values);

Value opDiv(std::stack<Op> &ops, std::stack<Value> &values);

Value opMod(std::stack<Op> &ops, std::stack<Value> &values);

Value opExp(std::stack<Op> &ops, std::stack<Value> &values);

Value opSqrt(std::stack<Op> &ops, std::stack<Value> &values);

Value opSin(std::stack<Op> &ops, std::stack<Value> &values);

Value opCos(std::stack<Op> &ops, std::stack<Value> &values);

Value opBand(std::stack<Op> &ops, std::stack<Value> &values);

Value opBor(std::stack<Op> &ops, std::stack<Value> &values);

Value opBxor(std::stack<Op> &ops, std::stack<Value> &values);

Number factorial(const Number &n);

Value opFactorial(std::stack<Op> &ops, std::stack<Value> &values);

Number combination(const Number &a, const Number &b);

Value opChoose(std::stack<Op> &ops, std::stack<Value> &values);

int gcd(int a, int b);

Value opGCD(std::stack<Op> &ops, std::stack<Value> &values);

Value opLCM(std::stack<Op> &ops, std::stack<Value> &values);

Value opLn(std::stack<Op> &ops, std::stack<Value> &values);

Value opLog(std::stack<Op> &ops, std::stack<Value> &values);

Value opTan(std::stack<Op> &ops, std::stack<Value> &values);

Value opCot(std::stack<Op> &ops, std::stack<Value> &values);

Value opSec(std::stack<Op> &ops, std::stack<Value> &values);

Value opCsc(std::stack<Op> &ops, std::stack<Value> &values);

Value opArcsin(std::stack<Op> &ops, std::stack<Value> &values);

Value opArccos(std::stack<Op> &ops, std::stack<Value> &values);

Value opArctan(std::stack<Op> &ops, std::stack<Value> &values);

Value opDot(std::stack<Op> &ops, std::stack<Value> &values);

Value opCross(std::stack<Op> &ops, std::stack<Value> &values);

Value opMag(std::stack<Op> &ops, std::stack<Value> &values);

Value opNorm(std::stack<Op> &ops, std::stack<Value> &values);

Value opType(std::stack<Op> &ops, std::stack<Value> &values);

Value opSum(std::stack<Op> &ops, std::stack<Value> &values);

Value opMin(std::stack<Op> &ops, std::stack<Value> &values);

Value opMax(std::stack<Op> &ops, std::stack<Value> &values);

Number binomialDensity(const Number &x, const Number &size, const Number &prob);

Value opDbinom(std::stack<Op> &ops, std::stack<Value> &values);

Number binomialDistribution(const Number &x, const Number &size, const Number &prob);

Value opPbinom(std::stack<Op> &ops, std::stack<Value> &values);

Number exponentialDensity(const Number &x, const Number &lambda);

Value opDexp(std::stack<Op> &ops, std::stack<Value> &values);

Number exponentialDistribution(const Number &x, const Number &lambda);

Value opPexp(std::stack<Op> &ops, std::stack<Value> &values);

Number uniformDensity(const Number &min, const Number &max);

Value opDunif(std::stack<Op> &ops, std::stack<Value> &values);

Number uniformDistribution(const Number &x, const Number &min, const Number &max);

Value opPunif(std::stack<Op> &ops, std::stack<Value> &values);

Number poissonDensity(const Number &x, const Number &lambda);

Value opDpois(std::stack<Op> &ops, std::stack<Value> &values);

Number poissonDistribution(const Number &x, const Number &lambda);

Value opPpois(std::stack<Op> &ops, std::stack<Value> &values);

Number hypergeometricDensity(const Number &x, const Number &m1, const Number &m2, const Number &n);

Value opDhyper(std::stack<Op> &ops, std::stack<Value> &values);

Number hypergeometricDistribution(const Number &x, const Number &m1, const Number &m2, const Number &n);

Value opPhyper(std::stack<Op> &ops, std::stack<Value> &values);

Number normalDensity(const Number &x, const Number &mean, const Number &sd);

Value opDnorm(std::stack<Op> &ops, std::stack<Value> &values);

Number normalDistribtion(const Number &x, const Number &mean, const Number &sd);

Value opPnorm(std::stack<Op> &ops, std::stack<Value> &values);


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
        {"mag",    {1, 4,  "mag",    opMag}},
        {"norm",   {1, 4,  "norm",   opNorm}},
        {"type",   {1, 4,  "type",   opType}},
        {"sum",    {1, 4,  "sum",    opSum}},
        {"min",    {1, 4,  "sum",    opMin}},
        {"max",    {1, 4,  "sum",    opMax}},
        {"logb",   {2, 4,  "logb",   opLog}},    // log_x(y)
        {"gcd",    {2, 4,  "gcd",    opGCD}},      // Greatest Common Divisor
        {"lcm",    {2, 4,  "lcm",    opLCM}},      // Least Common Multiple
        {"bxor",   {2, 4,  "bxor",   opBxor}},   // bxor(a, b) treated as (a ^ b)
        {"bor",    {2, 4,  "bor",    opBor}},      // bor(a, b) treated as (a | b)
        {"band",   {2, 4,  "band",   opBand}},   // band(a, b) treated as (a & b)
        {"mod",    {2, 4,  "mod",    opMod}},      // mod(a, b) treated as (a % b)
        {"exp",    {2, 4,  "exp",    opExp}},
        {"choose", {2, 4,  "choose", opChoose}},
        {"dot",    {2, 4,  "dot",    opDot}},
        {"cross",  {2, 4,  "cross",  opCross}},
        {"dexp",   {2, 4,  "dexp",   opDexp}},      // P(X = x)
        {"pexp",   {2, 4,  "pexp",   opPexp}},      // P(X < x)
        {"dpois",  {2, 4,  "dpois",  opDpois}},     // P(X = x)
        {"ppois",  {2, 4,  "ppois",  opPpois}},     // P(X < x)
        {"dbinom", {3, 4,  "dbinom", opDbinom}},    // P(X = x)
        {"pbinom", {3, 4,  "pbinom", opPbinom}},    // P(X < x)
        {"dunif",  {3, 4,  "dunif",  opDunif}},     // P(X = x)
        {"punif",  {3, 4,  "punif",  opPunif}},     // P(X < x)
        {"dnorm",  {3, 4,  "dnorm",  opDnorm}},     // P(X = x)
        {"pnorm",  {3, 4,  "pnorm",  opPnorm}},     // P(X < x)
        {"dhyper", {4, 4,  "dhyper", opDhyper}},    // P(X = x)
        {"phyper", {4, 4,  "phyper", opPhyper}},    // P(X < x)
};

const static std::unordered_map<std::string, double> constants = {
        {"e",   std::exp(1.0)},
        {"pi",  2 * std::acos(0.0)},
        {"phi", ((1 + sqrt(5)) / 2)},

};


#endif
