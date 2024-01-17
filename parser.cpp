#include "parser.h"

ASTNode Parser::parse(const std::vector<Token> &tokens) {
    ASTNode root;
    for (const auto &token : tokens) {
        if (token.type != TokenType::EndOfFile) {
            root.children.push_back({token.type, token.value});
        }
    }
    return root;
}