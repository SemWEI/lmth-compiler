#include <iostream>
#include <fstream>
#include <sstream>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

std::string readFile(const std::string &filePath) {
    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Could not open the file: " << filePath << std::endl;
        exit(1);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main() {
    std::cout << "Toy Compiler\n";

    Lexer lexer;
    Parser parser;
    CodeGen codegen;

    std::string templateSource = readFile("template.ts");

    auto tokens = lexer.tokenize(templateSource);
    auto ast = parser.parse(tokens);
    std::string generatedCode = codegen.generateCode(ast);

    std::ofstream outFile("output.ts");
    if (outFile) {
        outFile << generatedCode;
        std::cout << "Generated code written to output.ts" << std::endl;
    } else {
        std::cerr << "Could not write to output file." << std::endl;
    }

    return 0;
}