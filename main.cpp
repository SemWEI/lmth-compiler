#include <iostream>
#include "lexer.h"

int main() {
    std::cout << "Toy Compiler\n";

    // Initialize the Lexer, Parser, and CodeGen components
    Lexer lexer;
  
    // Input source code
    std::string source = "code here";

    // Lexing phase
    auto tokens = lexer.tokenize(source);

   

    return 0;
}
