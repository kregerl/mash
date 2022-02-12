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

std::unordered_map<std::string, double> Evaluator::s_variables = {};
std::unordered_map<std::string, Function> Evaluator::s_functions = {};

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
    double left = getValue(node.left());
    double right = getValue(node.right());
    switch (node.getType()) {
        case BinaryOpType::Plus: {
            result(left + right);
            break;
        }
        case BinaryOpType::Minus: {
            result(left - right);
            break;
        }
        case BinaryOpType::Multiply: {
            result(left * right);
            break;
        }
        case BinaryOpType::Divide: {
            if (right == 0) {
                throw EvaluatorException("Division by Zero");
            }
            result(left / right);
            break;
        }
        case BinaryOpType::Modulo: {
            // TODO: Look into double modulo
            result(static_cast<int>(left) % static_cast<int>(right));
            break;
        }
        case BinaryOpType::Exp: {
            result(std::pow(left, right));
            break;
        }
        case BinaryOpType::BW_Or: {
            // TODO: Casting to ints
            result(static_cast<int>(left) | static_cast<int>(right));
            break;
        }
        case BinaryOpType::BW_And: {
            // TODO: Casting to ints
            result(static_cast<int>(left) & static_cast<int>(right));
            break;
        }
        case BinaryOpType::BW_Xor: {
            // TODO: Casting to ints
            result(static_cast<int>(left) ^ static_cast<int>(right));
            break;
        }
        case BinaryOpType::BW_Shift_Right: {
            // TODO: Casting to ints
            result(static_cast<int>(left) >> static_cast<int>(right));
            break;
        }
        case BinaryOpType::BW_Shift_Left: {
            // TODO: Casting to ints
            result(static_cast<int>(left) << static_cast<int>(right));
            break;
        }
    }
}

void Evaluator::visit(const UnaryOpNode &node) {
    double child = getValue(node.getChild());
    switch (node.getType()) {
        case UnaryOpType::Negation: {
            result(-child);
            break;
        }
        case UnaryOpType::Factorial: {
            result(std::tgamma(child + 1));
            break;
        }
    }
}

void Evaluator::visit(const AssignmentNode &node) {
    double value = getValue(node.getValue());
    s_variables.emplace(node.getIdentifierStr(), value);
    result(value);
}

void Evaluator::visit(const FunctionNode &node) {
    std::unordered_map<std::string, double> tmp = s_variables;
    Function f = s_functions.at(node.getFunctionName());
    if (f.m_parameters.size() != node.getFunctionParameters().size()) {
        throw EvaluatorException("Too many parameters for function " + node.getFunctionName());
    }
    std::vector<std::string> params = f.m_parameters;
    for (int i = 0; i < params.size(); i++) {
        s_variables.emplace(params[i], getValue(node.getFunctionParameters()[i]));
    }
    double d = getValue(f.m_value);
    s_variables = tmp;
    result(d);
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

}

void PrettyPrinter::visit(const FunctionAssignmentNode &node) {

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
