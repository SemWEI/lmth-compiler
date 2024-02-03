#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"
#include "json.hpp"

using json = nlohmann::json;

struct ASTNode {
    TokenType type;
    std::string value;
    std::vector<ASTNode> children;
};

class Parser {
public:
    ASTNode parse(const std::vector<Token> &tokens);
    ASTNode parseJSON(const std::string &jsonStr);
};

#endif // PARSER_H