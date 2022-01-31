#include "Nodes.h"
#include "cmath"

NumberNode::NumberNode(const double &value) : m_value(value) {}

double NumberNode::getValue() const {
    return m_value;
}

UnaryOpNode::UnaryOpNode(UnaryOpType type, AbstractNode *child) : m_type(type), m_child(child) {}

UnaryOpType UnaryOpNode::getType() const {
    return m_type;
}

AbstractNode *UnaryOpNode::getChild() const {
    return m_child;
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

void Evaluator::visit(const NumberNode &node) {
    result(node.getValue());
}

void Evaluator::visit(const BinaryOpNode &node) {
    double left = getValue(node.left());
    double right = getValue(node.right());
    switch (node.getType()) {
        case BinaryOpType::Equals:
            break;
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
            // TODO: Make sure right is not 0
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
