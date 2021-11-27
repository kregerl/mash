#include "main.h"
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

// TODO: Convert double vectors in Vector and Set to Number vector.
// TODO: Allow colon syntax for vectors and sets: [1:6] -> {1, 2, 3, 4, 5, 6} | [:2] -> {0, 1, 2}
// TODO: Allow |x| syntax for absolute value, also add `abs(x)`


//#define DEBUG
std::unordered_map<std::string, Value> global_variables;
std::unordered_map<std::string, Function> functions;

int main() {
// f(x) = 2x
//    auto lexer = Lexer("(12.3 + 2.2) * 3");
    auto lexer = Lexer("-(-1.25 *- 2.25)");
    std::vector<Token> tokens = lexer.tokenize();
    auto parser = Parser(tokens);
    Node *node = parser.parse();
    auto interpreter = Interpreter();
    std::cout << interpreter.visit(node)->token << std::endl;
//    Node parser.parse();
//    for (auto &token : tokens) {
//        std::cout << token << std::endl;
//    }
//    tests();
    printf("Number of operators: %d\nNumber of constants: %d\n", operations.size(), constants.size());
    fflush(stdout);

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
                    // Read in all params and place them into the param list,
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
                    // Check each param to make sure they are actually used after the equals sign.
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
            std::cout << "Signature: " << functionSignature << std::endl;
            if (operations.find(var) != operations.end()) {
                std::cout << "Cannot have a variable named the same as an operator!" << std::endl;
                exit(1);
            } else if (functionSignature.find('(') == std::string::npos ||
                       functionSignature.find(')') == std::string::npos) {
                // If it doesn't have parens then it is a variable and not a function
                std::string expression = command.substr(eqPos + 1);
                global_variables[var] = evaluate(expression);
            }
            std::cout << std::endl;
        } else if (global_variables.find(command) != global_variables.end()) {
            std::cout << global_variables[command] << std::endl;
            global_variables["ans"] = global_variables[command];
        } else if (functions.find(command) != functions.end()) {
            printf("%s = %s\n", functions.at(command).name.c_str(), functions.at(command).expression.c_str());
        } else {
            // Otherwise just evaluate expression.
            Value val = evaluate(command);
            std::cout << val << std::endl;
            global_variables["ans"] = val;
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
    assert(("`123 + 10` was evaluated incorrectly", std::get<Number>(evaluate("123 + 10").getNum()).getRawDouble() ==
                                                    133));
    assert(("`10 - 10` was evaluated incorrectly", std::get<Number>(evaluate("10 - 10").getNum()).getRawDouble() == 0));
    assert(("`(10 * 5) / 5` was evaluated incorrectly",
            std::get<Number>(evaluate("(10 * 5) / 5").getNum()).getRawDouble() ==
            10));
    assert(("`(12 % 5) * 6` was evaluated incorrectly",
            std::get<Number>(evaluate("(12 % 5) * 6").getNum()).getRawDouble() ==
            12));
    assert(("`7 / 7 % 3` was evaluated incorrectly", std::get<Number>(evaluate("7 / 7 % 3").getNum()).getRawDouble() ==
                                                     1));
    assert(("`7 / (7 % 3)` was evaluated incorrectly",
            std::get<Number>(evaluate("7 / (7 % 3)").getNum()).getRawDouble() ==
            7));
    assert(("`7 / mod(7, 3)` was evaluated incorrectly",
            std::get<Number>(evaluate("7 / mod(7,3)").getNum()).getRawDouble() == 7));
    assert(("`exp(2, 3)` was evaluated incorrectly", std::get<Number>(evaluate("exp(2, 3)").getNum()).getRawDouble() ==
                                                     8));
    assert(("`2^3` was evaluated incorrectly", std::get<Number>(evaluate("2^3").getNum()).getRawDouble() == 8));
    assert(("`sqrt(mod(12, 5))` was evaluated incorrectly",
            std::get<Number>(evaluate("sqrt(mod(12, 5))").getNum()).getRawDouble() ==
            sqrt(12 % 5)));
    assert(("`2 | 3 + 1` was evaluated incorrectly", std::get<Number>(evaluate("2 | 3 + 1").getNum()).getRawDouble() ==
                                                     6));
    assert(("`bor(2, 3) + 1` was evaluated incorrectly",
            std::get<Number>(evaluate("bor(2, 3) + 1").getNum()).getRawDouble() == 4));
    assert(("`2 & 3 + 1` was evaluated incorrectly", std::get<Number>(evaluate("2 & 3 + 1").getNum()).getRawDouble() ==
                                                     0));
    assert(("`band(2, 3) + 1` was evaluated incorrectly",
            std::get<Number>(evaluate("band(2, 3) + 1").getNum()).getRawDouble() == 3));
    assert(("`3!` was evaluated incorrectly", std::get<Number>(evaluate("3!").getNum()).getRawDouble() == 6));
    assert(("`exp(2, 3!)` was evaluated incorrectly",
            std::get<Number>(evaluate("exp(2, 3!)").getNum()).getRawDouble() ==
            64));
    assert(("`12!` was evaluated incorrectly", std::get<Number>(evaluate("12!").getNum()).getRawDouble() == 479001600));
    assert(("`exp(2, mod(12!, 17))` was evaluated incorrectly",
            std::get<Number>(evaluate("exp(2, mod(12!, 17))").getNum()).getRawDouble() ==
            4096));
    assert(("`12.3` was evaluated incorrectly", std::get<Number>(evaluate("12.3").getNum()).getRawDouble() == 12.3));
    assert(("`11.245 / 1.353` was evaluated incorrectly",
            std::get<Number>(evaluate("11.245 / 1.353").getNum()).getRawDouble() ==
            11.245 / 1.353));
    assert(("`exp(1.124, 5.5)` was evaluated incorrectly",
            std::get<Number>(evaluate("exp(1.124, 5.5)").getNum()).getRawDouble() ==
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
    if (operations.find(op.token) != operations.end()) {
        Value res = op.func(ops, values);
        return res;
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

std::string oppositeToken(const char &token) {
    switch (token) {
        case '[': {
            return "]";
        }
        case ']': {
            return "[";
        }
        case '{': {
            return "}";
        }
        case '}': {
            return "{";
        }
        case '(': {
            return ")";
        }
        case ')': {
            return "(";
        }
        default: {
            return {1, token};
        }
    }
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
    std::stack<Op> ops;
    for (int i = 0; i < expression.length(); i++) {
        char token = expression[i];
        if (token == ' ') {
            continue;
        }
        // If this token is `0`, increment and the next token is `x`
        // TODO: Fix negative reading by checking for `-` here too. If its followed by digit or `.`, then number otherwise, operator.
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
                if (decimal.empty()) {
                    values.push({std::stod(number), NumberType::Integer});
                } else {
                    values.push(std::stod(number));
                }
                i--;
            }
            if (!ops.empty() && ops.top().token == "-") {
                values.push(applyOps(ops, values));
            }

        } else if (token == '(' || token == ',' || token == '[' || token == '{') {
            ops.push(operations.at(std::string(1, token)));
        } else if (token == ')') {
            // TODO: Apply these fixes for correct error handling to the other operations that do similar, `], }`
            int counter = 0;
            while (!ops.empty() && ops.top().token != oppositeToken(token)) {
                Op op = ops.top();
                if (op.token == ",") {
                    counter++;
                    ops.pop();
                    continue;
                } else {
                    values.push(applyOps(ops, values));
                }
            }
            if (!ops.empty() && ops.top().token == oppositeToken(token)) {
                ops.pop();
            } else {
                ops.push(operations.at(std::string(1, token)));
            }

            if (!ops.empty()) {
                Op top = ops.top();
                if (top.num_params > 0 && counter + 1 != top.num_params) {
                    fprintf(stderr, "Error: Operator `%s` requires %d parameters but received %d\n", top.token.c_str(),
                            top.num_params, counter + 1);
                    exit(1);
                }
            }
        } else if (token == ']' || token == '}') {
            // TODO: Allow collection to emplace a Number type to keep the types.
            Collection1D collection;
            if (!values.empty()) {
                // Only place doubles in the collection
                std::visit(overload{
                    [&collection, &values](Number &num) {
                        collection.emplace_back(num.getRawDouble());
                        values.pop();
                        },
                        [](auto &num) {
                        //                            No op
                    }
                    }, values.top().getNum());
            }
            while (ops.top().token != oppositeToken(token)) {
                Op op = ops.top();
                // numbers seperated by commas.
                if (op.token == ",") {
                    ops.pop();
                    if (!values.empty()) {
                        // Only place doubles in the collection
                        std::visit(overload{
                            [&collection, &values](Number &num) {
                                collection.emplace_back(num.getRawDouble());
                                values.pop();
                                },
                                [](auto &num) {
                                //                            No op
                            }
                            }, values.top().getNum());
                    }
                }
            }
            Op top = ops.top();
            ops.pop();
            if (token == ']' && top.token == oppositeToken(token)) {
                values.push(Vector(collection));
            } else if (token == '}' && top.token == oppositeToken(token)) {
                values.push(Set(collection));
            }

        } else if (token == '+' || token == '-' || token == '*' || token == '/' || token == '%' || token == '^' ||
        token == '&' || token == '|' || token == '!') {
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
            // i will point to the letter before the opening paren (`mod(x)`[i] -> 'd')
            if (constants.find(str) != constants.end()) {
                values.push(constants.at(str));
            } else if (variables.find(str) != variables.end() && operations.find(str) == operations.end()) {
                values.push(variables.at(str));
            } else if (functions.find(str) != functions.end()) {
                ops.push(functionToOp(functions.at(str)));
                if (expression[i] != '(') {
                    //                    std::cout << "Function Error" << std::endl;
                    Value v;
                    v.setError("Function Error");
                    return v;
                }
            } else if (variables.find(str) == variables.end() && operations.find(str) != operations.end()) {
                ops.push(operations.at(str));
                if (expression[i] != '(') {
                    //                    std::cout << "Operation Error" << std::endl;
                    Value v;
                    v.setError("Operation Error");
                    return v;
                }
            } else {
                std::cout << "ERROR: Token not found" << std::endl;
            }
            i--;
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


