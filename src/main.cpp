#include "main.h"
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Nodes.h"

// TODO: Convert double vectors in Vector and Set to Number vector.
// TODO: Allow colon syntax for vectors and sets: [1:6] -> {1, 2, 3, 4, 5, 6} | [:2] -> {0, 1, 2}
// TODO: Allow |x| syntax for absolute value, also add `abs(x)`


//std::unordered_map<std::string, NumberNode *> globalVariables;

int main() {
    std::string expression;
    auto interpreter = Interpreter();
    while (expression != "exit") {
        std::cout << "Mash > ";
        getline(std::cin, expression);
        if (expression == "exit") {
            break;
        } else {
            try {
                auto lexer = Lexer(expression);
                auto tokens = lexer.tokenize();
                auto parser = Parser(tokens);
                AbstractNode *n = parser.parse();
                std::cout << Evaluator::getValue(n) << std::endl;
            } catch (EvaluatorException &e) {
                std::cout << e.what() << std::endl;
            }
        }
    }
}


