#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter() {}

Interpreter::~Interpreter() {}

Token Interpreter::interpret(const std::string &expression) {
    auto lexer = Lexer(expression);
    auto tokens = lexer.tokenize();
    auto parser = Parser(tokens);
    Node *node = parser.parse();
    return node->calculate(variables)->token;
}

