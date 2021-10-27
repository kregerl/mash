#include <iostream>
#include <stack>
#include <cmath>
#include <cassert>
#include "main.h"

//#define DEBUG
static bool steps = true;

int main() {
    tests();
    std::string command;
    while (command != "exit") {
        std::cout << "Mash > ";
        getline(std::cin, command);
        if (command == "exit") {
            break;
        }
//        std::string assignment = command.substr(0, command.find("="));
//        std::string exp = command.substr(command.find("=") + 1);
//        std::cout << exp << std::endl;
//        std::cout << assignment << std::endl;
        std::cout << evaluate(command) << std::endl;
//        printf(OutputFormats[static_cast<int>(res.type)].c_str(), res);
    }

    return 0;
}

void tests() {
    assert(("`123 + 10` was evaluated incorrectly", evaluate("123 + 10") == 133));
    assert(("`10 - 10` was evaluated incorrectly", evaluate("10 - 10") == 0));
    assert(("`(10 * 5) / 5` was evaluated incorrectly", evaluate("(10 * 5) / 5") == 10));
    assert(("`(12 % 5) * 6` was evaluated incorrectly", evaluate("(12 % 5) * 6") == 12));
    assert(("`7 / 7 % 3` was evaluated incorrectly", evaluate("7 / 7 % 3") == 1));
    assert(("`7 / (7 % 3)` was evaluated incorrectly", evaluate("7 / (7 % 3)") == 7));
    assert(("`7 / mod(7, 3)` was evaluated incorrectly", evaluate("7 / mod(7,3)") == 7));
    assert(("`exp(2, 3)` was evaluated incorrectly", evaluate("exp(2, 3)") == 8));
    assert(("`2^3` was evaluated incorrectly", evaluate("2^3") == 8));
    assert(("`sqrt(mod(12, 5))` was evaluated incorrectly", evaluate("sqrt(mod(12, 5))") == sqrt(12 % 5)));
    assert(("`2 | 3 + 1` was evaluated incorrectly", evaluate("2 | 3 + 1") == 6));
    assert(("`bor(2, 3) + 1` was evaluated incorrectly", evaluate("bor(2, 3) + 1") == 4));
    assert(("`2 & 3 + 1` was evaluated incorrectly", evaluate("2 & 3 + 1") == 0));
    assert(("`band(2, 3) + 1` was evaluated incorrectly", evaluate("band(2, 3) + 1") == 3));
    assert(("`exp(2, (band(2, 3) + 1))` was evaluated incorrectly", evaluate("exp(2, (band(2, 3) + 1))") == 8));




}

double applyOps(std::stack<Op> &ops, std::stack<double> &values) {
    const Op op = ops.top();
    double result = 0;
    if (operations.count(op.token)) {
        Result res = op.func(ops, values);
        if (res.error) {
            printf("Error\n");
        }
        return res.num;
    } else {
        printf("Error, unknown operation.\n");
    }
    return result;
}

bool hasPrecedence(const Op &op1, const Op &op2) {
#ifdef DEBUG
    std::cout << "OP1: " << op1.token << std::endl;
    std::cout << "OP2: " << op2.token << std::endl;
#endif
    return op1.precedence <= op2.precedence;
}

double evaluate(const std::string &expression) {
    std::stack<double> values;
    std::stack<Op> ops;

    for (int i = 0; i < expression.length(); i++) {
        char token = expression[i];
        if (token == ' ') {
            continue;
        }
        if (std::isdigit(token)) {
            int num = 0;
            while (i < expression.length() && std::isdigit(expression[i])) {
//                if (expression[i] == ',') {
//                    break;
//                }
                num *= 10;
                num += expression[i++] - '0';
            }
            values.push(num);
            i--;
        } else if (token == '(' || token == ',') {
            ops.push(operations.at(std::string(1, token)));
        } else if (token == ')') {
            int counter = 0;
            while (ops.top().token != "(") {
                Op op = ops.top();
                if (op.token == ",") {
                    counter++;
                    ops.pop();
                    continue;
                } else {
                    values.push(applyOps(ops, values));
                }
            }
            ops.pop();

            if (!ops.empty()) {
                Op top = ops.top();
                if (top.num_params > 0 && counter + 1 != top.num_params) {
                    fprintf(stderr, "Error: Operator `%s` requires %d parameters but received %d\n", top.token.c_str(),
                            top.num_params, counter + 1);
                    exit(1);
                }
            }

        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%' || token == '^' ||
                   token == '&' || token == '|') {
            while (!ops.empty() && hasPrecedence(operations.at(std::string(1, token)), ops.top())) {
//                Op op = ops.top();
//                ops.pop();
                values.push(applyOps(ops, values));
            }
            ops.push(operations.at(std::string(1, token)));
        } else if (std::isalpha(token)) {
            // If it is a letter, continue reading letters until no more letters are found
            std::string str;
            while (i < expression.length() && std::isalpha(expression[i])) {
                str.push_back(expression[i++]);
            }
            i--;
            // i will point to the letter before the opening paren (`mod(x)`[i] -> 'd')
//            std::cout << expression[i] << std::endl;
            ops.push(operations.at(str));
        }
    }
#ifdef DEBUG
    std::cout << expression << std::endl;
    int c1 = 0;
    while (!values.empty()) {
        std::cout << c1++ << " :Values: " << values.top() << std::endl;
        values.pop();
    }
    int c2 = 0;
    while (!ops.empty()) {
        std::cout << c2++ << " :Ops: " << ops.top().token << std::endl;
        ops.pop();
    }
    return -1;
#endif


    while (!ops.empty()) {
        values.push(applyOps(ops, values));
    }
//    Result result = DEFAULT_RESULT;
//    result.error = false;
    double result = values.top();
    values.pop();
    return result;
}
