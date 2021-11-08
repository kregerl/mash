#include "main.h"
#include <sstream>

//#define DEBUG
std::unordered_map<std::string, Value> global_variables;
std::unordered_map<std::string, Function> functions;

int main() {
//    tests();
    printf("Number of operators: %d\nNumber of constants: %d\n", operations.size(), constants.size());
    fflush(stdout);

//    std::cout << derivative("2 * x^3") << std::endl;

    std::string command;
    while (command != "exit") {
        std::cout << "Mash > ";
        getline(std::cin, command);
        if (command == "exit") {
            break;
        }
        // Split the command by equals sign and assign a variable the value on the other side, otherwise just evaluate.
        int eqPos = static_cast<int>(command.find('='));
        if (eqPos > 0) {
            std::string var;
            for (int i = 0; i < eqPos; i++) {
                if (command[i] == ' ') {
                    continue;
                } else if ((std::isalpha(command[i]) || command[i] == '`') &&
                           constants.find(std::string(1, command[i])) == constants.end()) {
                    var.push_back(command[i]);
                } else if (command[i] == '(') {
                    // If function was already defined, remove it to be overwritten.
                    if (functions.find(var) != functions.end()) {
                        functions.erase(var);
                    }
                    functions[var].name = var;
                    std::cout << "Define function with name: " << var << std::endl;
                    while (i < eqPos && command[i] != ')') {
                        if (command[i] == ' ') {
                            i++;
                            continue;
                        } else if (std::isalpha(command[i])) {
                            functions[var].params.emplace_back(std::string(1, command[i++]));
                        } else {
                            i++;
                        }
                    }
                    std::reverse(functions.at(var).params.begin(), functions.at(var).params.end());
                    for (auto &param: functions.at(var).params) {
                        std::string expression = command.substr(eqPos + 1);
                        if (expression.find(param) == std::string::npos) {
                            std::cout << "Function must use every parameter at least once!" << std::endl;
                            exit(1);
                        }
                    }
                    functions.at(var).expression = command.substr(eqPos + 1, command.length());
                    std::cout << "Expression: " << functions.at(var).expression << std::endl;
                } else {
                    std::cout << "Cannot have a variable named the same as a constant!" << std::endl;
                    exit(1);
                }
            }

            std::string functionSignature = command.substr(0, eqPos);
            if (operations.find(var) != operations.end()) {
                std::cout << "Cannot have a variable named the same as an operator!" << std::endl;
                exit(1);
            } else if (functionSignature.find('(') == std::string::npos ||
                       functionSignature.find(')') == std::string::npos) {
                // No-op, just to prevent functions from being read as variables.
                std::string expression = command.substr(eqPos + 1);
                global_variables[var] = evaluate(expression);
            }
        } else if (global_variables.find(command) != global_variables.end()) {
            // If a command is a global variable.
            if (const std::vector<double> *vec = std::get_if<std::vector<double>>(&global_variables[command].num)) {
                std::array<char, 2> brackets = {};
                if ((global_variables[command].type & VECTOR) == VECTOR) {
                    brackets = {'[', ']'};
                } else if ((global_variables[command].type & SET) == SET) {
                    brackets = {'{', '}'};
                }

                std::cout << brackets[0];
                for (int i = vec->size() - 1; i >= 0; i--) {
                    if (i > 0) {
                        std::cout << vec->at(i) << ", ";
                    } else {
                        std::cout << vec->at(i);
                    }
                }
                std::cout << brackets[1] << std::endl;
            } else if (const double *dval = std::get_if<double>(&global_variables[command].num)) {
                printf("Result: %.20f\n", *dval);
                fflush(stdout);
            } else if (const int *ival = std::get_if<int>(&global_variables[command].num)) {
                printf("Result: %d\n", *ival);
                fflush(stdout);
            }

        } else if (functions.find(command) != functions.end()) {
            printf("%s = %s\n", functions.at(command).name.c_str(), functions.at(command).expression.c_str());
        } else {
            // Otherwise just evaluate expression.
            Value val = evaluate(command);
            if (const std::vector<double> *vec = std::get_if<std::vector<double>>(&val.num)) {
                std::array<char, 2> brackets = {};
                if ((val.type & VECTOR) == VECTOR) {
                    brackets = {'[', ']'};
                } else if ((val.type & SET) == SET) {
                    brackets = {'{', '}'};
                }

                std::cout << brackets[0];
                for (int i = vec->size() - 1; i >= 0; i--) {
                    if (i > 0) {
                        std::cout << vec->at(i) << ", ";
                    } else {
                        std::cout << vec->at(i);
                    }
                }
                std::cout << brackets[1] << std::endl;
            } else if (const double *dval = std::get_if<double>(&val.num)) {
                printf("Result: %.20f\n", *dval);
                fflush(stdout);
            } else if (const int *ival = std::get_if<int>(&val.num)) {
                printf("Result: %d\n", *ival);
                fflush(stdout);
            }
        }
    }

    return 0;
}

Op functionToOp(const Function &function) {
    Op op;
    op.token = function.name;
    op.precedence = 4;
    op.num_params = static_cast<int>(function.params.size());
    op.func = nullptr;
    return op;
}


void tests() {
    assert(("`123 + 10` was evaluated incorrectly", std::get<double>(evaluate("123 + 10").num) == 133));
    assert(("`10 - 10` was evaluated incorrectly", std::get<double>(evaluate("10 - 10").num) == 0));
    assert(("`(10 * 5) / 5` was evaluated incorrectly", std::get<double>(evaluate("(10 * 5) / 5").num) == 10));
    assert(("`(12 % 5) * 6` was evaluated incorrectly", std::get<double>(evaluate("(12 % 5) * 6").num) == 12));
    assert(("`7 / 7 % 3` was evaluated incorrectly", std::get<double>(evaluate("7 / 7 % 3").num) == 1));
    assert(("`7 / (7 % 3)` was evaluated incorrectly", std::get<double>(evaluate("7 / (7 % 3)").num) == 7));
    assert(("`7 / mod(7, 3)` was evaluated incorrectly", std::get<double>(evaluate("7 / mod(7,3)").num) == 7));
    assert(("`exp(2, 3)` was evaluated incorrectly", std::get<double>(evaluate("exp(2, 3)").num) == 8));
    assert(("`2^3` was evaluated incorrectly", std::get<double>(evaluate("2^3").num) == 8));
    assert(("`sqrt(mod(12, 5))` was evaluated incorrectly", std::get<double>(evaluate("sqrt(mod(12, 5))").num) ==
                                                            sqrt(12 % 5)));
    assert(("`2 | 3 + 1` was evaluated incorrectly", std::get<double>(evaluate("2 | 3 + 1").num) == 6));
    assert(("`bor(2, 3) + 1` was evaluated incorrectly", std::get<double>(evaluate("bor(2, 3) + 1").num) == 4));
    assert(("`2 & 3 + 1` was evaluated incorrectly", std::get<double>(evaluate("2 & 3 + 1").num) == 0));
    assert(("`band(2, 3) + 1` was evaluated incorrectly", std::get<double>(evaluate("band(2, 3) + 1").num) == 3));
    assert(("`3!` was evaluated incorrectly", std::get<double>(evaluate("3!").num) == 6));
    assert(("`exp(2, 3!)` was evaluated incorrectly", std::get<double>(evaluate("exp(2, 3!)").num) == 64));
    assert(("`12!` was evaluated incorrectly", std::get<double>(evaluate("12!").num) == 479001600));
    assert(("`exp(2, mod(12!, 17))` was evaluated incorrectly",
            std::get<double>(evaluate("exp(2, mod(12!, 17))").num) ==
            4096));
    assert(("`12.3` was evaluated incorrectly", std::get<double>(evaluate("12.3").num) == 12.3));
    assert(("`11.245 / 1.353` was evaluated incorrectly", std::get<double>(evaluate("11.245 / 1.353").num) ==
                                                          11.245 / 1.353));
    assert(("`exp(1.124, 5.5)` was evaluated incorrectly", std::get<double>(evaluate("exp(1.124, 5.5)").num) ==
                                                           pow(1.124, 5.5)));


}

/**
 * Call the top operator's operation function and return the result
 * @param ops - Operation stack
 * @param values - Value stack
 * @return The result of the top operator applied to the value stack
 */
Value applyOps(std::stack<Op> &ops, std::stack<Value> &values) {
    const Op op = ops.top();
    double result = 0;
    if (operations.count(op.token)) {
        Result res = op.func(ops, values);
        if (!res.error.empty()) {
            printf("%s\n", res.error.c_str());
        }
        return res.num;
    } else if (functions.find(op.token) != functions.end()) {
        ops.pop();
        std::unordered_map<std::string, Value> variables;
        Function function = functions.at(op.token);
        size_t paramsSize = function.params.size();
        if (values.size() >= paramsSize) {
            for (int i = 0; i < paramsSize; i++) {
                variables[function.params.at(i)] = values.top();
                values.pop();
            }
            return evaluate(function.expression, variables);
        }
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

/**
 * Evaluate will evaluate the expression with the global variable map.
 * @param expression The expression to evaluate
 * @return The result of the  expression
 */
Value evaluate(const std::string &expression) {
    return evaluate(expression, global_variables);
}

/**
 * Evaluate will evaluate the expression with the specific variable map passed by variables
 * @param expression The expression to evaluate
 * @param variables The list of variables that are valid for expression
 * @return The result of the expression evaluated with the variables
 */
Value evaluate(const std::string &expression, std::unordered_map<std::string, Value> &variables) {
    std::stack<Value> values;
//    std::stack<Value> vals;
//    std::vector<double> vec = {10.0, 9, 8, 7, 6, 5};
//    vals.push(vec);
//    Value v = vals.top();
//    for (auto &num : *std::get_if<std::vector<double>>(&v)) {
//        std::cout << num << std::endl;
//    }
    std::stack<Op> ops;
    for (int i = 0; i < expression.length(); i++) {
        char token = expression[i];
        if (token == ' ') {
            continue;
        }
        // If this token is `0`, increment and the next token is `x`
        if (std::isdigit(token) || token == '.') {
            // Read hex numbers and convert them to integers on the values stack.
            if (expression[i] == '0' && std::tolower(expression[i + 1]) == 'x') {
                i += 2;
                std::string num;
                while (i < expression.length() && std::isdigit(token)) {
                    num.push_back(expression[i++]);
                }
                int n;
                std::istringstream(num) >> std::hex >> n;
                values.push(n);
            } else {
                std::string number;
                while (i < expression.length() && std::isdigit(expression[i])) {
                    number.push_back(expression[i++]);
                }
                std::string decimal;
                if (expression[i] == '.') {
                    while (i < expression.length() && std::isdigit(expression[++i])) {
                        decimal.push_back(expression[i]);
                    }
                    number.push_back('.');
                    number.append(decimal);
                }
//                if (decimal.empty()) {
//                    values.push(std::stoi(number));
//                } else {
//                    values.push(std::stod(number));
//                }
                values.push(std::stod(number));
                i--;
            }
        } else if (token == '!') {
            // TODO: Check if the char in front is a number, if not check if it is a variable.
            if (i - 1 >= 0 && std::isdigit(expression[i - 1])) {
                ops.push(operations.at(std::string(1, token)));
                values.push(applyOps(ops, values));
            } else {
                std::cout << "Must have the factorial operator next to a number!" << std::endl;
            }
        } else if (token == '(' || token == ',' || token == '[' || token == '{') {
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
        } else if (token == ']' || token == '}') {
//            if ((values.top().type & INTEGER) == INTEGER) {
//
//            } else if ((values.top().type & DOUBLE) == DOUBLE) {
//
//            }
            std::vector<double> val;
            if (!values.empty()) {
                val.emplace_back(std::get<double>(values.top().num));
                values.pop();
            }
            while (ops.top().token != "[" && ops.top().token != "{") {
                Op op = ops.top();
                if (op.token == ",") {
                    ops.pop();
                    if (!values.empty()) {
                        val.emplace_back(std::get<double>(values.top().num));
                        values.pop();
                    }
                }
            }
            Op top = ops.top();
            ops.pop();
            if (token == ']' && top.token == "[") {
                values.push({val, VECTOR});
            } else if (token == '}' && top.token == "{") {
                values.push({val, SET});
            } else {
                fprintf(stderr, "Syntax Error: missing bracket\n");
                fflush(stderr);
            }

        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%' || token == '^' ||
                   token == '&' || token == '|') {
            while (!ops.empty() && hasPrecedence(operations.at(std::string(1, token)), ops.top())) {
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
            if (constants.find(str) != constants.end()) {
                values.push(constants.at(str));
            } else if (variables.find(str) != variables.end() && operations.find(str) == operations.end()) {
                values.push(variables.at(str));
            } else if (functions.find(str) != functions.end()) {
                ops.push(functionToOp(functions.at(str)));
            } else if (variables.find(str) == variables.end() && operations.find(str) != operations.end()) {
                ops.push(operations.at(str));
            } else {
                std::cout << "ERROR: Token not found" << std::endl;
            }
        }
    }
#ifdef DEBUG
    std::cout << expression << std::endl;
    int c1 = 0;
    while (!values.empty()) {
        std::cout << c1++ << " :Values: " << std::get<double>(values.top()) << std::endl;
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
    Value result = values.top();
    values.pop();
    return result;

}
