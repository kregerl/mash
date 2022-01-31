#include "Interpreter.h"
#include <iostream>

Interpreter::Interpreter() {}

Interpreter::~Interpreter() {}

double Interpreter::interpret(const std::string &expression) {
    auto lexer = Lexer(expression);
    auto tokens = lexer.tokenize();
    auto parser = Parser(tokens);
    AbstractNode *node = parser.parse();


}

//Token Interpreter::interpret(const std::string &expression) {
//    auto lexer = Lexer(expression);
//    auto tokens = lexer.tokenize();
//    auto parser = Parser(tokens);
//    Node *node = parser.parse();
//    return node->calculate(variables)->token;
//}

