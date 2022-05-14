#include "main.h"
#include <sstream>
#include <iomanip>
#include <unistd.h>
#include <filesystem>
#include <fstream>

#include "Interpreter.h"
#include "Nodes.h"

int main(int argc, char **argv) {
    auto interpreter = Interpreter();
    if (argc == 2) {
        std::ifstream file(argv[1]);
        std::stringstream buffer;
        buffer << file.rdbuf();
        interpreter.interpret(buffer.str());
        return 0;
    }

    if (argc == 3) {
        std::string flag = argv[1];
        if (flag == "-i") {
            if (std::filesystem::exists(argv[2])) {
                std::cout << "HERE" << std::endl;
            }
            interpreter.interpret(argv[2]);
            return 0;
        } else if (flag == "-precision") {
            interpreter.setPrecision(std::stoi(argv[2]));
        }
    }


    std::string expression;
    // If the input is piped in, not typed by the user.
    if (!isatty(STDIN_FILENO)) {
        getline(std::cin, expression);
        interpreter.interpret(expression);
        return 0;
    }
    // TODO: Make these tokens that preform this when noticed in the expression. Pretty much like variables with a different use case.
    while (true) {
        std::cout << "Mash > ";
        getline(std::cin, expression);
        if (expression == "exit") {
            break;
        } else if (expression == "clear") {
            system("clear");
        } else if (expression == "lsv") {
            for (const auto &entry : Evaluator::s_variables) {
                std::cout << std::setprecision(interpreter.getPrecision()) << entry.first << ": ";
                std::visit(overload{
                        [](const NumericLiteral &d) { std::cout << d << std::endl; },
                        [](const StringLiteral &d) { std::cout << d << std::endl; },
                        [](auto &a) { std::cout << "Unknown" << std::endl; }
                }, entry.second);
            }
        } else if (expression == "lsf") {
            for (const auto &entry : Evaluator::s_functions) {
                std::cout << entry.first << ": (";
                for (int i = 0; i < entry.second.m_parameters.size(); i++) {
                    std::string param = entry.second.m_parameters[i];
                    if (i < entry.second.m_parameters.size() - 1) {
                        std::cout << param << ", ";
                    } else {
                        std::cout << param;
                    }
                }
                std::cout << ")" << std::endl;
            }
        } else {
            interpreter.interpret(expression);
        }
    }
}



