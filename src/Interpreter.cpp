#include "Interpreter.h"
#include "Lexer.h"
#include "Nodes.h"
#include "Parser.h"
#include <iostream>
#include<iomanip>

void Interpreter::interpret(const std::string &expression) {
    try {
        auto lexer = Lexer(expression);
        auto tokens = lexer.tokenize();
        auto parser = Parser(tokens);
        AbstractNode *n = parser.parse();
        Returnable v = Evaluator::getValue(n);
        if (m_precision == -1) {
            std::visit(overload{
                    [](NumericLiteral &d) { std::cout << d << std::endl; },
                    [](Collection &c) { std::cout << c << std::endl; },
                    [](auto &a) { std::cout << "Not supported yet" << std::endl; }
            }, v);
        } else {
            int p = m_precision;
            std::visit(overload{
                    [&p](NumericLiteral &d) { std::cout << std::setprecision(p) << d << std::endl;; },
                    [](auto &a) { std::cout << "Not supported yet" << std::endl; }
            }, v);

        }
    } catch (EvaluatorException &e) {
        std::cout << e.what() << std::endl;
    } catch (TokenizeException &e) {
        std::cout << e.what() << std::endl;
    }
}

void Interpreter::setPrecision(int precision) {
    m_precision = precision;
}

int Interpreter::getPrecision() const {
    return m_precision;
}


