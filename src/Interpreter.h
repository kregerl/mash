#ifndef MASH_INTERPRETER_H
#define MASH_INTERPRETER_H

#include <string>

class Interpreter {
public:
    static int precision;

    Interpreter() : m_precision(-1) {}

    void interpret(const std::string& expression);

    void setPrecision(int precision);

    int getPrecision() const;

private:
    int m_precision;
};

#endif //MASH_INTERPRETER_H
