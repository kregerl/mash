#ifndef MASH_NODES_H
#define MASH_NODES_H

#include "Lexer.h"
#include <optional>
#include <unordered_map>
#include <memory>

#define VISITABLE virtual void accept(Visitor &visitor) override {visitor.visit(*this);}

enum class UnaryOpType {
    Negation = 0, Factorial
};
enum class BinaryOpType {
    Equals = 0, Plus, Minus, Multiply, Divide, Modulo, Exp, BW_Or, BW_And, BW_Xor, BW_Shift_Left, BW_Shift_Right
};

class NumberNode;

class BinaryOpNode;

class UnaryOpNode;

class Visitor {
public:
    virtual void visit(const NumberNode &node) = 0;

    virtual void visit(const BinaryOpNode &node) = 0;

    virtual void visit(const UnaryOpNode &node) = 0;

};


class AbstractNode {
public:
    virtual ~AbstractNode() = default;

    virtual void accept(Visitor &visitor) = 0;
};

class NumberNode : public AbstractNode {
public:
    VISITABLE

    NumberNode(const double &value);

    double getValue() const;

private:
    double m_value;
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

    void result(ResultType result);

private:
    ResultType value;
};


class Evaluator : public ValueGetter<Evaluator, AbstractNode *, double>, public Visitor {
public:
    virtual void visit(const NumberNode &node);

    virtual void visit(const BinaryOpNode &node);

    virtual void visit(const UnaryOpNode &node);
};

//class NumberNode;
//
//class Node {
//public:
//    virtual ~Node() = default;
//
//    virtual NumberNode *calculate(std::unordered_map<std::string, NumberNode *> &variables) = 0;
//};
//
//class NumberNode : public Node {
//public:
//    explicit NumberNode(const Token &token);
//
//    explicit NumberNode(const std::string &str);
//
//    NumberNode *calculate(std::unordered_map<std::string, NumberNode *> &variables) override;
//
//    friend std::ostream &operator<<(std::ostream &os, const NumberNode &node);
//
//public:
//    Token token;
//    std::optional<std::string> errorMessage;
//};
//
//class UnaryOpNode : public Node {
//public:
//    explicit UnaryOpNode(const Token &token, Node *child);
//
//    ~UnaryOpNode() override;
//
//    NumberNode *calculate(std::unordered_map<std::string, NumberNode *> &variables) override;
//
//public:
//    Token token;
//    Node *child;
//};
//
//class BinaryOpNode : public Node {
//public:
//    explicit BinaryOpNode(const Token &token, Node *left, Node *right);
//
//    ~BinaryOpNode() override;
//
//    NumberNode *calculate(std::unordered_map<std::string, NumberNode *> &variables) override;
//
//public:
//    Token token;
//    Node *left;
//    Node *right;
//};

#endif //MASH_NODES_H
