#include "Interpreter.h"
#include "Lexer.h"
#include "Nodes.h"
#include "Parser.h"
#include <iostream>
#include <iomanip>
#include <bitset>
#include <sstream>
#include <algorithm>

#define BINARY_PRECISION 32

void Interpreter::interpret(const std::string &expression) {
    try {
        auto lexer = Lexer(expression);
        auto tokens = lexer.tokenize();
        auto parser = Parser(tokens);
        AbstractNode *n = parser.parse();
        Returnable v = Evaluator::getValue(n);
        if (m_precision == -1) {
            std::visit(overload{
                    [](NumericLiteral &n) {
                        switch (n.getInternalType()) {
                            case InternalType::Double:
                            case InternalType::Integer: {
                                std::cout << n.getValue() << std::endl;
                                break;
                            }
                            case InternalType::Hex: {
                                std::stringstream stream;
                                stream << std::hex << static_cast<int>(n.getValue());
                                std::string result(stream.str());
                                std::transform(result.begin(), result.end(), result.begin(), ::toupper);
                                std::cout << "0x" << result << " (" << n.getValue() << ")" << std::endl;
                                break;
                            }
                            case InternalType::Binary: {
                                std::cout << std::bitset<BINARY_PRECISION>(static_cast<int>(n.getValue())).to_string()
                                          << " ("
                                          << n.getValue() << ")" << std::endl;
                                break;
                            }
                        }


                    },
                    [](StringLiteral &s) { std::cout << s << std::endl; },
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


