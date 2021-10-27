#ifndef MASH_MAIN_H
#define MASH_MAIN_H
#include "Operations.h"

void tests();
double applyOps(std::stack<Op> &ops, std::stack<double> &values);
bool hasPrecedence(Op &op1, Op &op2);
double evaluate(const std::string &expression);

#endif
