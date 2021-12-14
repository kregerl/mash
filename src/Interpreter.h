#ifndef MASH_INTERPRETER_H
#define MASH_INTERPRETER_H

#include <unordered_map>
#include "Parser.h"

class Interpreter {
public:
    Interpreter();

    ~Interpreter();

    double evaluate();

private:
    std::unordered_map<std::string, Node *> variables;
    std::unordered_map<std::string, Node *> functions;

};


#endif //MASH_INTERPRETER_H
