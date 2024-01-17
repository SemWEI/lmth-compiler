#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

enum class TokenType {
    Identifier,
    Placeholder,
    Text,
    EndOfFile
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    std::vector<Token> tokenize(const std::string &source);
};

#endif // LEXER_H