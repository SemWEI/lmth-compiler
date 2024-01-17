#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include "lexer.h"

struct ASTNode {
    TokenType type;
    std::string value;
    std::vector<ASTNode> children;
};

class Parser {
public:
    ASTNode parse(const std::vector<Token> &tokens);
};

#endif // PARSER_H