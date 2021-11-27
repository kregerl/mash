#ifndef MASH_INTERPRETER_H
#define MASH_INTERPRETER_H


#include "Parser.h"

class Interpreter {
public:
    Interpreter();

    ~Interpreter();

    Node *visit(Node *ast);

    Node *visitNumber(Node *node);

    Node *visitAdd(Node *node);

    Node *visitSub(Node *node);

    Node *visitMul(Node *node);

private:

};


#endif //MASH_INTERPRETER_H
