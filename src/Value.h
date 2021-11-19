#ifndef MASH_VALUE_H
#define MASH_VALUE_H

#include <variant>
#include <vector>
#include <optional>

#include "Number.h"
#include "Set.h"
#include "Vector.h"


template<class... Ts>
struct overload : Ts ... {
    using Ts::operator()...;
};
template<class... Ts> overload(Ts...) -> overload<Ts...>;


class Value {
public:
    Value();

    Value(double n, NumberType type = NumberType::Double);

    Value(Number n);

    Value(Vector n);

    Value(Set n);

    Value(std::vector<double> n, NumberType type);

    ~Value() = default;

    friend std::ostream &operator<<(std::ostream &os, const Value &val);

    std::variant<Number, Vector, Set> &getNum();

    void setNum(const Value &n);

    std::optional<std::string> getMessage();

    void setMessage(const std::string &s);

    void setError(const std::string &s);

    std::optional<std::string> getError();

    NumberType getType() const;

    Value &operator=(const Value &val);

    Value &operator=(const double &val);


private:
    std::variant<Number, Vector, Set> m_num;
    std::optional<std::string> m_messaage;
    std::optional<std::string> m_error;


};


#endif //MASH_VALUE_H
