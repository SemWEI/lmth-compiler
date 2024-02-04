#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

namespace fs = std::filesystem;

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

    std::string jsonSource = readFile("template.json");
    auto astData = parser.parseJSON(jsonSource);

    std::string templateDir = "templates";

    for (const auto &entry : fs::directory_iterator(templateDir)) {
        if (entry.is_regular_file()) {
            std::string templateSource = readFile(entry.path().string());
            auto tokens = lexer.tokenize(templateSource);
            auto astTemplate = parser.parse(tokens);
            std::string generatedCode = codegen.generateCode(astTemplate, astData);

            std::string outputFileName = "output_" + entry.path().stem().string() + ".ts";
            std::ofstream outFile(outputFileName);
            if (outFile) {
                outFile << generatedCode;
                std::cout << "Generated code written to " << outputFileName << std::endl;
            } else {
                std::cerr << "Could not write to output file " << outputFileName << std::endl;
            }
        }
    }

    return 0;
}
