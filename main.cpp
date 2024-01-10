#include <iostream>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

int main() {
    std::cout << "Toy Compiler\n";

    // Initialize the Lexer, Parser, and CodeGen components
    Lexer lexer;
    Parser parser;
    CodeGen codegen;

    std::string source = "sample";

    auto tokens = lexer.tokenize(source);

    auto ast = parser.parse(tokens);

    codegen.generateCode(ast);

    return 0;
}