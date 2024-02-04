#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "lexer.h"
#include "parser.h"
#include "codegen.h"

namespace fs = std::filesystem;

// Function to read file contents
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
    Lexer lexer;
    Parser parser;
    CodeGen codegen;

    // Read and parse the model.json file
    std::string jsonSource = readFile("model.json");
    auto astData = parser.parseJSON(jsonSource);

    // Directories for Angular and Express.js templates
    std::string angularTemplateDir = "templates/angular";
    std::string expressTemplateDir = "templates/express";

    // Process Angular templates
    for (const auto &entry : fs::directory_iterator(angularTemplateDir)) {
        if (entry.is_regular_file()) {
            std::string templateSource = readFile(entry.path().string());
            auto tokens = lexer.tokenize(templateSource);
            auto astTemplate = parser.parse(tokens);
            std::string generatedCode = codegen.generateCode(astTemplate, astData);

            std::string outputFileName = "output/angular/" + entry.path().stem().string() + ".ts";
            std::ofstream outFile(outputFileName);
            if (outFile) {
                outFile << generatedCode;
                std::cout << "Generated Angular code written to " << outputFileName << std::endl;
            } else {
                std::cerr << "Could not write to output file " << outputFileName << std::endl;
            }
        }
    }

    // Process Express.js templates
    for (const auto &entry : fs::directory_iterator(expressTemplateDir)) {
        if (entry.is_regular_file()) {
            std::string templateSource = readFile(entry.path().string());
            auto tokens = lexer.tokenize(templateSource);
            auto astTemplate = parser.parse(tokens);
            std::string generatedCode = codegen.generateCode(astTemplate, astData);

            std::string outputFileName = "output/express/" + entry.path().stem().string() + ".js";
            std::ofstream outFile(outputFileName);
            if (outFile) {
                outFile << generatedCode;
                std::cout << "Generated Express.js code written to " << outputFileName << std::endl;
            } else {
                std::cerr << "Could not write to output file " << outputFileName << std::endl;
            }
        }
    }

    return 0;
}