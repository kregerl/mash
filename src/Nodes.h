#ifndef MASH_NODES_H
#define MASH_NODES_H

#include "Lexer.h"
#include "Literal.h"
#include <optional>
#include <unordered_map>
#include <memory>
#include <string>
#include <variant>
#include <map>

#define VISITABLE virtual void accept(Visitor &visitor) override {visitor.visit(*this);}

#define UNORDERED_VISIT(type1, type2, expression) \
                        [](type1 &a, type2 &b) -> Returnable {\
                            return std::visit(overload{\
                                    [&a](NumericLiteral &b) -> Returnable { return expression; },\
                                    [](auto &b) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }\
                                }, s_variables.at(b));\
                            },\
                        [](type2 &a, type1 &b) -> Returnable {\
                            return std::visit(overload{\
                                    [&b](NumericLiteral &a) -> Returnable { return expression; },\
                                    [](auto &a) -> Returnable { throw EvaluatorException("Unsupported Operation!"); }\
                                }, s_variables.at(a));\
                            },                    \

#define UNORDERED_VISIT_FUNCTION(type1, type2, function) \
                        [](type1 &a, type2 &b) -> Returnable {\
                            return function(a, b); \
                        },\
                        [](type2 &a, type1 &b) -> Returnable {\
                            return function(a, b);\
                        },\

enum class UnaryOpType {
    Negation = 0,
    Factorial,
    SquareRoot,
    Sine,
    Cosine,
    Tangent,
    Cotangent,
    Secant,
    Cosecant,
    ArcSine,
    ArcCosine,
    ArcTangent,
    AbsoluteValue,
    Log,
    NaturalLog,
    ToHex,
    Sum
};
enum class BinaryOpType {
    Plus = 0,
    Minus,
    Multiply,
    Divide,
    Modulo,
    Exp,
    BW_Or,
    BW_And,
    BW_Xor,
    BW_Shift_Left,
    BW_Shift_Right,
    LogBase,
    VectorSlice,
    LessThan,
    GreaterThan
};

enum class CollectionType {
    Set = 0, Vector
};


class NumberNode;

class StringNode;

class IdentifierNode;

class BinaryOpNode;

class UnaryOpNode;

class AssignmentNode;

class FunctionNode;

class FunctionAssignmentNode;

class VectorNode;

class ProgramNode;

class BlockNode;

class PrintNode;

class ConditionalNode;

class Visitor {
public:
    virtual void visit(const NumberNode &node) = 0;

    virtual void visit(const IdentifierNode &node) = 0;

    virtual void visit(const StringNode &node) = 0;

    virtual void visit(const BinaryOpNode &node) = 0;

    virtual void visit(const UnaryOpNode &node) = 0;

    virtual void visit(const AssignmentNode &node) = 0;

    virtual void visit(const FunctionNode &node) = 0;

    virtual void visit(const FunctionAssignmentNode &node) = 0;

    virtual void visit(const VectorNode &node) = 0;

    virtual void visit(const ProgramNode &node) = 0;

    virtual void visit(const BlockNode &node) = 0;

    virtual void visit(const PrintNode &node) = 0;

    virtual void visit(const ConditionalNode &node) = 0;
};


class AbstractNode {
public:
    virtual ~AbstractNode() = default;

    virtual void accept(Visitor &visitor) = 0;
};

template<typename T>
class ValueNode : public AbstractNode {
public:

    explicit ValueNode(T value);

    virtual T getValue() const;

private:
    T m_value;
};


class NumberNode : public ValueNode<NumericLiteral> {
public:
    VISITABLE

    explicit NumberNode(NumericLiteral value);
};

class StringNode : public ValueNode<StringLiteral> {
public:
    VISITABLE

    explicit StringNode(StringLiteral value);
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

class FunctionNode : public AbstractNode {
public:
    VISITABLE

    FunctionNode(IdentifierNode *name, std::vector<AbstractNode *> parameters);

    IdentifierNode *getIdentifier() const;

    std::string getFunctionName() const;

    std::vector<AbstractNode *> getFunctionParameters() const;

private:
    IdentifierNode *m_functionName;
    std::vector<AbstractNode *> m_functionParameters;
};

class FunctionAssignmentNode : public AbstractNode {
public:
    VISITABLE

    FunctionAssignmentNode(FunctionNode *function, AbstractNode *value);

    FunctionNode *getFunctionNode() const;

    AbstractNode *getValue() const;

private:
    FunctionNode *m_functionNode;
    AbstractNode *m_value;
};

class VectorNode : public AbstractNode {
public:
    VISITABLE

    explicit VectorNode(const std::vector<AbstractNode *> &children);

    std::vector<AbstractNode *> getChildren() const;

private:
    std::vector<AbstractNode *> m_children;
};

class StatementNode : public AbstractNode {
public:
    void accept(Visitor &v) override = 0;
};

class ProgramNode : public AbstractNode {
public:
    VISITABLE

    explicit ProgramNode(std::vector<AbstractNode *> nodes);

public:
    std::vector<AbstractNode *> statements;
};

class BlockNode : public AbstractNode {
public:
    VISITABLE

    explicit BlockNode(std::vector<AbstractNode *> statements);

public:
    std::vector<AbstractNode *> statements;
};

class PrintNode : public AbstractNode {
public:
    VISITABLE

    explicit PrintNode(AbstractNode *expression);

public:
    AbstractNode *expression;
};

class ConditionalNode : public AbstractNode {
public:
    VISITABLE

    explicit ConditionalNode(AbstractNode *condition, AbstractNode *ifBlock,
                             std::map<AbstractNode *, AbstractNode *> &elifs);

    explicit ConditionalNode(AbstractNode *condition, AbstractNode *ifBlock,
                             std::map<AbstractNode *, AbstractNode *> &elifs, AbstractNode *elseBlock);

public:
    AbstractNode *condition;
    AbstractNode *ifBlock;
    AbstractNode *elseBlock;
    std::map<AbstractNode *, AbstractNode *> elifs;
};


template<typename Visitor, typename Visitable, typename ResultType>
class ValueGetter {
public:
    ValueGetter() = default;

    static ResultType getValue(Visitable v);

    virtual void result(ResultType result);

protected:
    ResultType value;
};

class Function {
public:
    Function(std::vector<std::string> parameters, AbstractNode *value) : m_parameters(parameters), m_value(value) {}

public:
    std::vector<std::string> m_parameters;
    AbstractNode *m_value;
};


template<class... Ts>
struct overload : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overload(Ts...) -> overload<Ts...>;

struct Collection;
// TODO: Replace the double and string with literals, override all the operators.
using Returnable = std::variant<NumericLiteral, StringLiteral, std::string, Collection>;

struct Collection {
    CollectionType type;
    std::vector<Returnable> elements;

    friend std::ostream &operator<<(std::ostream &os, const Collection &c) {
        std::string left, right;
        switch (c.type) {
            case CollectionType::Set: {
                left = "{";
                right = "}";
                break;
            }
            case CollectionType::Vector: {
                left = "[";
                right = "]";
                break;
            }
        }
        os << left;
        for (int i = 0; i < c.elements.size(); i++) {
            auto element = c.elements[i];
            std::visit(overload{
                    [&os](NumericLiteral &d) { os << std::to_string(d.getValue()); },
                    [&os](Collection &c) { os << c; },
                    [&os](auto &a) { os << std::string("Unknown type!"); }
            }, element);
            if (i < c.elements.size() - 1) {
                os << std::string(", ");
            }
        }
        os << right;
        return os;
    }
};


class Evaluator : public ValueGetter<Evaluator, AbstractNode *, Returnable>, public Visitor {
public:
    Evaluator() = default;

    void visit(const NumberNode &node) override;

    void visit(const IdentifierNode &node) override;

    virtual void visit(const StringNode &node) override;

    void visit(const BinaryOpNode &node) override;

    void visit(const UnaryOpNode &node) override;

    void visit(const AssignmentNode &node) override;

    void visit(const FunctionNode &node) override;

    void visit(const FunctionAssignmentNode &node) override;

    void visit(const VectorNode &node) override;

    void visit(const ProgramNode &node) override;

    void visit(const BlockNode &node) override;

    void visit(const PrintNode &node) override;

    void visit(const ConditionalNode &node) override;

public:
    static std::unordered_map<std::string, Returnable> s_variables;
    static std::unordered_map<std::string, Function> s_functions;
};


class PrettyPrinter : public ValueGetter<PrettyPrinter, AbstractNode *, std::string>, public Visitor {
public:
    void visit(const NumberNode &node) override;

    void visit(const IdentifierNode &node) override;

    virtual void visit(const StringNode &node) override;

    void visit(const BinaryOpNode &node) override;

    void visit(const UnaryOpNode &node) override;

    void visit(const AssignmentNode &node) override;

    void visit(const FunctionNode &node) override;

    void visit(const FunctionAssignmentNode &node) override;

    void visit(const VectorNode &node) override;

    void visit(const ProgramNode &node) override;

    void visit(const BlockNode &node) override;

    void visit(const PrintNode &node) override;

    void visit(const ConditionalNode &node) override;


protected:
    static int s_indent;
};


class EvaluatorException : public std::exception {
public:
    explicit EvaluatorException(const std::string &message) : msg(message) {}

    ~EvaluatorException() noexcept override = default;

    virtual const char *what() const noexcept {
        return msg.c_str();
    }


private:
    std::string msg;
};

#endif //MASH_NODES_H
