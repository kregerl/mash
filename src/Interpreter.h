#ifndef MASH_INTERPRETER_H
#define MASH_INTERPRETER_H

#include <unordered_map>
#include "Parser.h"



class Interpreter {
public:
    Interpreter();

    ~Interpreter();

    double interpret(const std::string &expression);


private:
//    std::unordered_map<std::string, NumberNode *> variables;
//    std::unordered_map<std::string, NumberNode *> functions;

};

class EvaluatorException : public std::exception {
};

#endif //MASH_INTERPRETER_H
