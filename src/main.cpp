#include "main.h"
#include <sstream>

#include "Lexer.h"
#include "Parser.h"
#include "Interpreter.h"

// TODO: Convert double vectors in Vector and Set to Number vector.
// TODO: Allow colon syntax for vectors and sets: [1:6] -> {1, 2, 3, 4, 5, 6} | [:2] -> {0, 1, 2}
// TODO: Allow |x| syntax for absolute value, also add `abs(x)`



int main() {
    auto lexer = Lexer("-xyz + 3");
    std::vector<Token> tokens = lexer.tokenize();
    auto parser = Parser(tokens);
    Node *node = parser.parse();
    std::unordered_map<std::string, NumberNode *> map;
    map.insert({"xyz", new NumberNode(Token("5", TokenType::Number))});
    std::cout << *node->calculate(map) << std::endl;
    exit(1);
}


