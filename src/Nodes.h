#ifndef MASH_NODES_H
#define MASH_NODES_H

#include "Lexer.h"
#include <optional>
#include <unordered_map>
#include <memory>
#include <string>

#define VISITABLE virtual void accept(Visitor &visitor) override {visitor.visit(*this);}

enum class UnaryOpType {
    Negation = 0, Factorial
};
enum class BinaryOpType {
    Plus = 0, Minus, Multiply, Divide, Modulo, Exp, BW_Or, BW_And, BW_Xor, BW_Shift_Left, BW_Shift_Right
};

enum class CollectionType {
    Set = 0, Vector
};

class NumberNode;

class IdentifierNode;

class BinaryOpNode;

class UnaryOpNode;

class AssignmentNode;

class Visitor {
public:
    virtual void visit(const NumberNode &node) = 0;

    virtual void visit(const IdentifierNode &node) = 0;

    virtual void visit(const BinaryOpNode &node) = 0;

    virtual void visit(const UnaryOpNode &node) = 0;

    virtual void visit(const AssignmentNode &node) = 0;

};


class AbstractNode {
public:
    virtual ~AbstractNode() = default;

    virtual void accept(Visitor &visitor) = 0;
};

template<typename T>
class ValueNode : public AbstractNode {
public:

    ValueNode(T value);

    virtual T getValue() const;

private:
    T m_value;
};


class NumberNode : public ValueNode<double> {
public:
    VISITABLE

    explicit NumberNode(double value);
};

class IdentifierNode : public ValueNode<std::string> {
public:
    VISITABLE

    explicit IdentifierNode(const std::string &value);
};

class UnaryOpNode : public AbstractNode {
public:
    VISITABLE

    UnaryOpNode(UnaryOpType type, AbstractNode *child);

    UnaryOpType getType() const;

    AbstractNode *getChild() const;


private:
    UnaryOpType m_type;
    AbstractNode *m_child;
};

class AssignmentNode : public AbstractNode {
public:
    VISITABLE

    AssignmentNode(IdentifierNode *var, AbstractNode *value);

    AbstractNode *getValue() const;

    IdentifierNode *getIdentifier() const;

    std::string getIdentifierStr() const;

private:
    IdentifierNode *var;
    AbstractNode *value;
};

class BinaryOpNode : public AbstractNode {
public:
    VISITABLE

    BinaryOpNode(BinaryOpType, AbstractNode *left, AbstractNode *right);


    BinaryOpType getType() const;

    AbstractNode *left() const;

    AbstractNode *right() const;

private:
    BinaryOpType m_type;
    AbstractNode *m_left;
    AbstractNode *m_right;
};


template<typename Visitor, typename Visitable, typename ResultType>
class ValueGetter {
public:
    static ResultType getValue(Visitable v);

    virtual void result(ResultType result);

protected:
    ResultType value;
};


class Evaluator : public ValueGetter<Evaluator, AbstractNode *, double>, public Visitor {
public:
    virtual void visit(const NumberNode &node) override;

    virtual void visit(const IdentifierNode &node) override;

    virtual void visit(const BinaryOpNode &node) override;

    virtual void visit(const UnaryOpNode &node) override;

    virtual void visit(const AssignmentNode &node) override;

private:
    static std::unordered_map<std::string, double> s_variables;
};


class PrettyPrinter : public ValueGetter<PrettyPrinter, AbstractNode *, std::string>, public Visitor {
public:
    virtual void visit(const NumberNode &node) override;

    virtual void visit(const IdentifierNode &node) override;

    virtual void visit(const BinaryOpNode &node) override;

    virtual void visit(const UnaryOpNode &node) override;

    virtual void visit(const AssignmentNode &node) override;

protected:
    static int s_indent;
};


class EvaluatorException : public std::exception {
public:
    explicit EvaluatorException(const std::string &message) : msg(message) {}

    virtual ~EvaluatorException() noexcept {}

    virtual const char *what() const noexcept {
        return msg.c_str();
    }


private:
    std::string msg;
};

#endif //MASH_NODES_H
