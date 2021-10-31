#ifndef MASH_MAIN_H
#define MASH_MAIN_H

#include "Operations.h"
typedef struct {
    std::string name;
    std::vector<std::string> params;
    std::string expression;
} Function;

void tests();
Op functionToOp(const Function &function);
double applyOps(std::stack<Op> &ops, std::stack<double> &values);
bool hasPrecedence(Op &op1, Op &op2);
double evaluate(const std::string &expression);
double evaluate(const std::string &expression, std::unordered_map<std::string, double> &variables);

#endif
