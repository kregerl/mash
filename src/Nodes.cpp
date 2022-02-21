#include "Nodes.h"
#include "cmath"
#include <sstream>

template<typename T>
ValueNode<T>::ValueNode(T value) : m_value(value) {}

template<typename T>
T ValueNode<T>::getValue() const {
    return m_value;
}

NumberNode::NumberNode(double value) : ValueNode(value) {}

IdentifierNode::IdentifierNode(const std::string &value) : ValueNode(value) {}

UnaryOpNode::UnaryOpNode(UnaryOpType type, AbstractNode *child) : m_type(type), m_child(child) {}

UnaryOpType UnaryOpNode::getType() const {
    return m_type;
}

AbstractNode *UnaryOpNode::getChild() const {
    return m_child;
}

AssignmentNode::AssignmentNode(IdentifierNode *var, AbstractNode *value) : var(var), value(value) {}

AbstractNode *AssignmentNode::getValue() const {
    return value;
}

IdentifierNode *AssignmentNode::getIdentifier() const {
    return var;
}

std::string AssignmentNode::getIdentifierStr() const {
    return var->getValue();
}

BinaryOpNode::BinaryOpNode(BinaryOpType type, AbstractNode *left, AbstractNode *right) : m_type(type), m_left(left),
                                                                                         m_right(right) {}

BinaryOpType BinaryOpNode::getType() const {
    return m_type;
}

AbstractNode *BinaryOpNode::left() const {
    return m_left;
}

AbstractNode *BinaryOpNode::right() const {
    return m_right;
}

FunctionNode::FunctionNode(IdentifierNode *name, std::vector<AbstractNode *> parameters) : m_functionName(name),
                                                                                           m_functionParameters(
                                                                                                   parameters) {}

IdentifierNode *FunctionNode::getIdentifier() const {
    return m_functionName;
}

std::string FunctionNode::getFunctionName() const {
    return m_functionName->getValue();
}

std::vector<AbstractNode *> FunctionNode::getFunctionParameters() const {
    return m_functionParameters;
}

FunctionAssignmentNode::FunctionAssignmentNode(FunctionNode *function, AbstractNode *value) : m_functionNode(function),
                                                                                              m_value(value) {}

AbstractNode *FunctionAssignmentNode::getValue() const {
    return m_value;
}

FunctionNode *FunctionAssignmentNode::getFunctionNode() const {
    return m_functionNode;
}

std::unordered_map<std::string, Returnable> Evaluator::s_variables = {
        {"pi", M_PI},
        {"e",   std::exp(1.0)},
        {"phi", ((1 + sqrt(5)) / 2)}
};
std::unordered_map<std::string, Function> Evaluator::s_functions = {
        {"sin",    Function({"x"}, new UnaryOpNode(UnaryOpType::Sine, new IdentifierNode("x")))},
        {"cos",    Function({"x"}, new UnaryOpNode(UnaryOpType::Cosine, new IdentifierNode("x")))},
        {"tan",    Function({"x"}, new UnaryOpNode(UnaryOpType::Tangent, new IdentifierNode("x")))},
        {"cot",    Function({"x"}, new UnaryOpNode(UnaryOpType::Cotangent, new IdentifierNode("x")))},
        {"sec",    Function({"x"}, new UnaryOpNode(UnaryOpType::Secant, new IdentifierNode("x")))},
        {"csc",    Function({"x"}, new UnaryOpNode(UnaryOpType::Cosecant, new IdentifierNode("x")))},
        {"arcsin", Function({"x"}, new UnaryOpNode(UnaryOpType::ArcSine, new IdentifierNode("x")))},
        {"arccos", Function({"x"}, new UnaryOpNode(UnaryOpType::ArcCosine, new IdentifierNode("x")))},
        {"arctan", Function({"x"}, new UnaryOpNode(UnaryOpType::ArcTangent, new IdentifierNode("x")))},
        {"sqrt",   Function({"x"}, new UnaryOpNode(UnaryOpType::SquareRoot, new IdentifierNode("x")))},
        {"abs",    Function({"x"}, new UnaryOpNode(UnaryOpType::AbsoluteValue, new IdentifierNode("x")))},
        {"log",    Function({"x"}, new UnaryOpNode(UnaryOpType::Log, new IdentifierNode("x")))},
        {"ln",     Function({"x"}, new UnaryOpNode(UnaryOpType::NaturalLog, new IdentifierNode("x")))},
        {"logb",   Function({"x", "y"},
                            new BinaryOpNode(BinaryOpType::LogBase, new IdentifierNode("x"), new IdentifierNode("y")))},
        {"exp",    Function({"x", "y"},
                            new BinaryOpNode(BinaryOpType::Exp, new IdentifierNode("x"), new IdentifierNode("y")))}
};

template<typename Visitor, typename Visitable, typename ResultType>
ResultType ValueGetter<Visitor, Visitable, ResultType>::getValue(Visitable v) {
    Visitor visitor;
    v->accept(visitor);
    return visitor.value;
}

template<typename Visitor, typename Visitable, typename ResultType>
void ValueGetter<Visitor, Visitable, ResultType>::result(ResultType result) {
    value = result;
}


void Evaluator::visit(const NumberNode &node) {
    result(node.getValue());
}

void Evaluator::visit(const IdentifierNode &node) {
    if (s_variables.find(node.getValue()) == s_variables.end()) {
        throw EvaluatorException("Cannot use a variable that has not been initialized!");
    } else {
        result(s_variables.at(node.getValue()));
    }
}

void Evaluator::visit(const BinaryOpNode &node) {
    Returnable left = getValue(node.left());
    Returnable right = getValue(node.right());
    switch (node.getType()) {
        case BinaryOpType::Plus: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return a + b; },
                    UNORDERED_VISIT(double, std::string, a + b)
                    [](Collection &a, Collection &b) -> Returnable { return Vector::addition(a, b); },
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::Minus: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return a - b; },
                    UNORDERED_VISIT(double, std::string, a - b)
                    [](Collection &a, Collection &b) -> Returnable { return Vector::subtraction(a, b); },
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::Multiply: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return a * b; },
                    UNORDERED_VISIT(double, std::string, a * b)
                    UNORDERED_VISIT_FUNCTION(double, Collection, Vector::scalarMultiplication)
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::Divide: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable {
                        if (b == 0) {
                            throw EvaluatorException("Division by Zero");
                        }
                        return a / b;
                    },
                    [](double &a, std::string &b) -> Returnable {
                        return std::visit(overload{
                                [&a](double &b) -> Returnable {
                                    if (b == 0) {
                                        throw EvaluatorException("Division by Zero");
                                    }
                                    return a / b;
                                },
                                [](auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(b));
                    },
                    [](std::string &a, double &b) -> Returnable {
                        return std::visit(overload{
                                [&b](double &a) -> Returnable {
                                    if (b == 0) {
                                        throw EvaluatorException("Division by Zero");
                                    }
                                    return a / b;
                                },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::Modulo: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) % static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) % static_cast<int>(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::Exp: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return std::pow(a, b); },
                    UNORDERED_VISIT(double, std::string, std::pow(a, b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::BW_Or: {
            // TODO: Casting to ints
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) | static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) | static_cast<int>(b))

                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::BW_And: {
            // TODO: Casting to ints
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) & static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) & static_cast<int>(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::BW_Xor: {
            // TODO: Casting to ints
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) ^ static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) ^ static_cast<int>(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::BW_Shift_Right: {
            // TODO: Casting to ints
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) >> static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) >> static_cast<int>(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::BW_Shift_Left: {
            // TODO: Casting to ints
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return static_cast<int>(a) << static_cast<int>(b); },
                    UNORDERED_VISIT(double, std::string, static_cast<int>(a) << static_cast<int>(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
        case BinaryOpType::LogBase: {
            result(std::visit(overload{
                    [](double &a, double &b) -> Returnable { return std::log(a) / std::log(b); },
                    UNORDERED_VISIT(double, std::string, std::log(a) / std::log(b))
                    [](auto &a, auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
            }, left, right));
            break;
        }
    }
}

void Evaluator::visit(const UnaryOpNode &node) {
    Returnable child = getValue(node.getChild());
    switch (node.getType()) {
        case UnaryOpType::Negation: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return a * -1; },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return a * -1; },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Factorial: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::tgamma(a + 1); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::tgamma(a + 1); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::SquareRoot: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::sqrt(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::sqrt(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Sine: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::sin(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::sin(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Cosine: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::cos(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::cos(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Tangent: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::tan(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::tan(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Cosecant: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return 1 / std::sin(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return 1 / std::sin(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Secant: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return 1 / std::cos(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return 1 / std::cos(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Cotangent: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return 1 / std::tan(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return 1 / std::tan(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::ArcSine: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::asin(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::asin(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::ArcCosine: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::acos(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::acos(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::ArcTangent: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::atan(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::atan(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::AbsoluteValue: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::abs(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::abs(a); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
        case UnaryOpType::Log: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::log(a) / std::log(10); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::log(a) / std::log(10); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;

        }
        case UnaryOpType::NaturalLog: {
            result(std::visit(overload{
                    [](double &a) -> Returnable { return std::log(a); },
                    [](std::string &a) -> Returnable {
                        return std::visit(overload{
                                [](double &a) -> Returnable { return std::log(10); },
                                [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }
                        }, s_variables.at(a));
                    },
                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }}, child));
            break;
        }
    }
}

void Evaluator::visit(const AssignmentNode &node) {
    Returnable value = getValue(node.getValue());
    s_variables.emplace(node.getIdentifierStr(), value);
    result(value);
}

void Evaluator::visit(const FunctionNode &node) {
    std::unordered_map<std::string, Returnable> tmp = s_variables;
    s_variables.clear();
    Function f = s_functions.at(node.getFunctionName());
    if (f.m_parameters.size() != node.getFunctionParameters().size()) {
        throw EvaluatorException("Too many parameters for function " + node.getFunctionName());
    }
    std::vector<std::string> params = f.m_parameters;
    for (int i = 0; i < params.size(); i++) {
        s_variables.emplace(params[i], getValue(node.getFunctionParameters()[i]));
    }
    Returnable v = getValue(f.m_value);
    s_variables = tmp;
    result(v);
}

void Evaluator::visit(const FunctionAssignmentNode &node) {
    FunctionNode *fNode = node.getFunctionNode();
    std::string funcName = fNode->getFunctionName();
    std::vector<std::string> params;
    for (auto node : fNode->getFunctionParameters()) {
        auto *in = dynamic_cast<IdentifierNode *>(node);
        if (in != nullptr) {
            params.emplace_back(in->getValue());
        } else {
            throw EvaluatorException("You must declare a function with variable parameters!");
        }
    }

    if (s_functions.find(funcName) != s_functions.end()) {
        s_functions.erase(funcName);
    }

    s_functions.emplace(funcName, Function(params, node.getValue()));
    result(0);
}

void Evaluator::visit(const VectorNode &node) {
    Collection c = {CollectionType::Vector, {}};
    for (auto n : node.getChildren()) {
        c.elements.emplace_back(getValue(n));
    }
    result(c);
}

int PrettyPrinter::s_indent = 0;

void PrettyPrinter::visit(const NumberNode &node) {
    std::stringstream ss;

    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    ss << "|-";
    ss << '(' << std::to_string(node.getValue()) << ')' << '\n';
    result(ss.str());
}


void PrettyPrinter::visit(const BinaryOpNode &node) {
    std::string nodeOp;
    switch (node.getType()) {
        case BinaryOpType::Plus: {
            nodeOp = "(+)\n";
            break;
        }
        case BinaryOpType::Minus: {
            nodeOp = "(-)\n";
            break;
        }
        case BinaryOpType::Multiply: {
            nodeOp = "(*)\n";
            break;
        }
        case BinaryOpType::Divide: {
            nodeOp = "(/)\n";
            break;
        }
        case BinaryOpType::Modulo: {
            nodeOp = "(%)\n";
            break;
        }
        case BinaryOpType::Exp: {
            nodeOp = "(**)\n";
            break;
        }
        case BinaryOpType::BW_Or: {
            nodeOp = "(|)\n";
            break;
        }
        case BinaryOpType::BW_And: {
            nodeOp = "(&)\n";
            break;
        }
        case BinaryOpType::BW_Xor: {
            nodeOp = "(^)\n";
            break;
        }
        case BinaryOpType::BW_Shift_Right: {
            nodeOp = "(>>)\n";
            break;
        }
        case BinaryOpType::BW_Shift_Left: {
            nodeOp = "(<<)\n";
            break;
        }
        case BinaryOpType::LogBase: {
            nodeOp = "(log_x(y))\n";
            break;
        }
    }
    std::stringstream ss;
    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    if (s_indent != 0) {
        ss << "|";
    }
    ss << "-BinaryOpNode" << nodeOp;
    s_indent += 2;
    ss << getValue(node.left());
    ss << getValue(node.right());
    s_indent -= 2;
    result(ss.str());
}

void PrettyPrinter::visit(const UnaryOpNode &node) {
    std::string nodeOp;
    switch (node.getType()) {
        case UnaryOpType::Negation: {
            nodeOp = "(-)\n";
            break;
        }
        case UnaryOpType::Factorial: {
            nodeOp = "(!)\n";
            break;
        }
        case UnaryOpType::SquareRoot: {
            nodeOp = "{sqrt(x)}\n";
            break;
        }
        case UnaryOpType::Sine: {
            nodeOp = "{sin(x)}\n";
            break;
        }
        case UnaryOpType::Cosine: {
            nodeOp = "{cos(x)}\n";
            break;
        }
        case UnaryOpType::Tangent: {
            nodeOp = "{tan(x)}\n";
            break;
        }
        case UnaryOpType::Cotangent: {
            nodeOp = "{cot(x)}\n";
            break;
        }
        case UnaryOpType::Secant: {
            nodeOp = "{sec(x)}\n";
            break;
        }
        case UnaryOpType::Cosecant: {
            nodeOp = "{csc(x)}\n";
            break;
        }
        case UnaryOpType::ArcSine: {
            nodeOp = "{arcsin(x)}\n";
            break;
        }
        case UnaryOpType::ArcCosine: {
            nodeOp = "{arccos(x)}\n";
            break;
        }
        case UnaryOpType::ArcTangent: {
            nodeOp = "{arctan(x)}\n";
            break;
        }
        case UnaryOpType::AbsoluteValue: {
            nodeOp = "{abs(x)}\n";
            break;
        }
        case UnaryOpType::Log: {
            nodeOp = "{log(x)}\n";
            break;
        }
        case UnaryOpType::NaturalLog: {
            nodeOp = "{ln(x)}\n";
            break;
        }
    }
    std::stringstream ss;
    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    if (s_indent != 0) {
        ss << "|";
    }
    ss << "-UnaryOpNode" << nodeOp;
    s_indent += 2;
    ss << getValue(node.getChild());
    s_indent -= 2;
    result(ss.str());
}

void PrettyPrinter::visit(const IdentifierNode &node) {
    std::stringstream ss;

    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    ss << "|-";
    ss << '(' << node.getValue() << ')' << '\n';
    result(ss.str());
}

void PrettyPrinter::visit(const AssignmentNode &node) {
    std::stringstream ss;
    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    if (s_indent != 0) {
        ss << "|";
    }
    ss << "-AssignmentNode" << "(=)\n";
    s_indent += 2;
    ss << getValue(node.getIdentifier());
    ss << getValue(node.getValue());
    s_indent -= 2;
    result(ss.str());
}

void PrettyPrinter::visit(const FunctionNode &node) {
    std::stringstream ss;
    for (int i = 0; i < s_indent; i++) {
        ss << " ";
    }
    if (s_indent != 0) {
        ss << "|";
    }
    //TODO: format this better
    ss << "-FunctionNode" << "(" << node.getFunctionName() << "())\n";
    s_indent += 2;
    ss << getValue(node.getIdentifier());
    for (auto n : node.getFunctionParameters()) {
        ss << getValue(n);
    }
    s_indent -= 2;
    result(ss.str());
}

void PrettyPrinter::visit(const FunctionAssignmentNode &node) {

}

void PrettyPrinter::visit(const VectorNode &node) {

}

VectorNode::VectorNode(const std::vector<AbstractNode *> &children) : m_children(children) {}

std::vector<AbstractNode *> VectorNode::getChildren() const {
    return m_children;
}
