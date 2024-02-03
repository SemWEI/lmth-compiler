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

    // Initialize the Lexer, Parser, and CodeGen components
    Lexer lexer;
    Parser parser;
    CodeGen codegen;

    // Input template source code
    std::string templateSource = readFile("template.ts");

    // Lexing phase
    auto tokens = lexer.tokenize(templateSource);

    // Parsing phase (template tokens)
    auto astTemplate = parser.parse(tokens);

    // Input JSON data
    std::string jsonSource = readFile("test.json");

    // Parsing phase (JSON data)
    auto astData = parser.parseJSON(jsonSource);

    // Code generation phase
    std::string generatedCode = codegen.generateCode(astTemplate, astData);

    // Output the generated code
    std::ofstream outFile("output.ts");
    if (outFile) {
        outFile << generatedCode;
        std::cout << "Generated code written to output.ts" << std::endl;
    } else {
        std::cerr << "Could not write to output file." << std::endl;
    }

    return 0;
}