#include "lexer.h"
#include <cctype>

std::vector<Token> Lexer::tokenize(const std::string &source) {
    std::vector<Token> tokens;
    std::string::const_iterator it = source.begin();

    while (it != source.end()) {
        if (*it == '$' && *(it + 1) == '{') {
            // Placeholder token
            std::string placeholder;
            it += 2; // Skip over '${'
            while (it != source.end() && *it != '}') {
                placeholder += *it++;
            }
            if (it != source.end()) ++it; // Skip over '}'
            tokens.push_back({TokenType::Placeholder, placeholder});
        } else {
            // Text token
            std::string text;
            while (it != source.end() && !(*it == '$' && *(it + 1) == '{')) {
                text += *it++;
            }
            tokens.push_back({TokenType::Text, text});
        }
    }

    tokens.push_back({TokenType::EndOfFile, ""});
    return tokens;
}