#include <gtest/gtest.h>
#include <Interpreter.h>

class OperatorTest : public ::testing::Test {
protected:
    virtual void SetUp() {

    }

    virtual void TearDown() {}
};

Token TOKEN(std::string s) {
    return Token(s, TokenType::Number);
}

TEST_F(OperatorTest, operators) {
    auto i = Interpreter();
    ASSERT_EQ(i.interpret("1 + 1"), TOKEN("2.000000")) << "1 + 1 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("1 - 1"), TOKEN("0.000000")) << "1 - 1 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("10 + 2"), TOKEN("12.000000")) << "10 + 2 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("10 - 1"), TOKEN("9.000000")) << "10 - 1 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("1123456"), TOKEN("1123456")) << "1123456 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("((1123456))+2"), TOKEN("1123456")) << "1123456 Evaluated incorrectly";

    ASSERT_EQ(i.interpret("-1 + 3"), TOKEN("2.000000")) << "-1 + 3 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("-(3 + -2) * -3"), TOKEN("3.000000")) << "-(3 + -2) * -3 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("---------7"), TOKEN("-7.000000")) << "---------7 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("3 * 7"), TOKEN("21.000000")) << "---------7 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("21 / 7"), TOKEN("3.000000")) << "---------7 Evaluated incorrectly";

    ASSERT_EQ(i.interpret("0!"), TOKEN("1.000000")) << "---------7 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("-1!"), TOKEN("inf")) << "---------7 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("13!"), TOKEN("6227020800.000000")) << "---------7 Evaluated incorrectly";
    ASSERT_EQ(i.interpret("3 + (10 - 2)!"), TOKEN("40323.000000")) << "---------7 Evaluated incorrectly";

}