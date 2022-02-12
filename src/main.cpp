#include "main.h"
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"
#include "Nodes.h"

// TODO: Convert double vectors in Vector and Set to Number vector.
// TODO: Allow colon syntax for vectors and sets: [1:6] -> {1, 2, 3, 4, 5, 6} | [:2] -> {0, 1, 2}


//std::unordered_map<std::string, NumberNode *> globalVariables;

int main(int argc, char **argv) {
    if (argc == 1) {
        std::string expression;
        auto interpreter = Interpreter();
        while (true) {
            std::cout << "Mash > ";
            getline(std::cin, expression);
            if (expression == "exit") {
                break;
            } else if (expression == "clear") {
                system("clear");
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
    } else {
        if (argc == 3) {
            std::string flag = argv[1];
            if (flag == "-i") {
                try {
                    auto lexer = Lexer(argv[2]);
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

}


