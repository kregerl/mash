#ifndef MASH_MATHUTIL_H

namespace Vector {
    static Collection scalarMultiplication(Collection &c, NumericLiteral scalar) {
        Collection res = {CollectionType::Vector, {}};
        for (auto elem : c.elements) {
            res.elements.emplace_back(std::visit(overload{
                    [&scalar](NumericLiteral &d) -> Returnable { return scalar * d; },
                    [](auto &a) -> Returnable {
                        throw EvaluatorException("Scalar Multiplication not supported on specified types.");
                    }
            }, elem));
        }
        return res;
    }

    static Collection scalarMultiplication(NumericLiteral scalar, Collection &c) {
        return scalarMultiplication(c, scalar);
    }

    static Collection scalarDivision(NumericLiteral scalar, Collection &c) {
        Collection res = {CollectionType::Vector, {}};
        if (scalar == 0) {
            throw EvaluatorException("Error, division by zero!");
        }
        for (auto elem : c.elements) {
            res.elements.emplace_back(std::visit(overload{
                    [&scalar](NumericLiteral &d) -> Returnable { return d / scalar; },
                    [](auto &a) -> Returnable {
                        throw EvaluatorException("Scalar Multiplication not supported on specified types.");
                    }
            }, elem));
        }
        return res;
    }

    static Collection scalarDivision(Collection &c, NumericLiteral scalar) {
        return scalarDivision(scalar, c);
    }

    static Collection scalarModulo(NumericLiteral scalar, Collection &c) {
        Collection res = {CollectionType::Vector, {}};
        if (scalar == 0) {
            throw EvaluatorException("Error, division by zero!");
        }
        for (auto elem : c.elements) {
            res.elements.emplace_back(std::visit(overload{
                    [&scalar](NumericLiteral &d) -> Returnable {
                        return d % scalar;
                    },
                    [](auto &a) -> Returnable {
                        throw EvaluatorException("Scalar Multiplication not supported on specified types.");
                    }
            }, elem));
        }
        return res;
    }

    static Collection scalarModulo(Collection &c, NumericLiteral scalar) {
        return scalarModulo(scalar, c);
    }


    static Collection addition(Collection &c1, Collection &c2) {
        Collection res = {CollectionType::Vector, {}};
        if (c1.elements.size() != c2.elements.size())
            throw EvaluatorException("Cannot add vectors of different dimensions.");
        for (int i = 0; i < c1.elements.size(); i++) {
            Returnable e1 = c1.elements[i];
            Returnable e2 = c2.elements[i];
            res.elements.emplace_back(std::visit(overload{
                    [](NumericLiteral &a, NumericLiteral &b) -> Returnable { return a + b; },
                    [](auto &a, auto &b) -> Returnable {
                        throw EvaluatorException("Unknown vector operation between types.");
                    }
            }, e1, e2));
        }
        return res;
    }

    static Collection subtraction(Collection &c1, Collection &c2) {
        Collection res = {CollectionType::Vector, {}};
        if (c1.elements.size() != c2.elements.size())
            throw EvaluatorException("Cannot add vectors of different dimensions.");
        for (int i = 0; i < c1.elements.size(); i++) {
            Returnable e1 = c1.elements[i];
            Returnable e2 = c2.elements[i];
            res.elements.emplace_back(std::visit(overload{
                    [](NumericLiteral &a, NumericLiteral &b) -> Returnable { return a - b; },
                    [](auto &a, auto &b) -> Returnable {
                        throw EvaluatorException("Unknown vector operation between types.");
                    }
            }, e1, e2));
        }
        return res;
    }

    static NumericLiteral dotProduct(Collection &c1, Collection &c2) {
        NumericLiteral sum;
        if (c1.elements.size() != c2.elements.size()) {
            throw EvaluatorException("Cannot dot two vectors of different sizes.");
        }
        for (int i = 0; i < c1.elements.size(); i++) {
            Returnable e1 = c1.elements[i];
            Returnable e2 = c2.elements[i];
            sum += std::visit(overload{
                    [](NumericLiteral &a, NumericLiteral &b) -> NumericLiteral { return a * b; },
                    [](auto &a, auto &b) -> NumericLiteral {
                        throw EvaluatorException("Unknown vector operation between types.");
                    }
            }, e1, e2);
        }
        return sum;
    }

    static NumericLiteral sum(Collection &c) {
        NumericLiteral sum;
        for (auto &element : c.elements) {
            sum += std::visit(overload{
                    [](NumericLiteral &a) -> NumericLiteral { return a; },
                    [](auto &a) -> NumericLiteral {
                        throw EvaluatorException("Unknown vector operation between types.");
                    }
            }, element);
        }
        return sum;
    }

}


#endif //MASH_MATHUTIL_H
