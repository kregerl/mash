#ifndef MASH_MAIN_H
#define MASH_MAIN_H
#include <cassert>
#include "Operations.h"
typedef struct {
    std::string name;
    std::vector<std::string> params;
    std::string expression;
} Function;

void tests();
Op functionToOp(const Function &function);
Value applyOps(std::stack<Op> &ops, std::stack<Value> &values);
bool hasPrecedence(Op &op1, Op &op2);
Value evaluate(const std::string &expression);
Value evaluate(const std::string &expression, std::unordered_map<std::string, Value> &variables);

#endif
