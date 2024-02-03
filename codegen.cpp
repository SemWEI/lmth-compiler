#include "codegen.h"
#include <sstream>
#include <unordered_map>

// Helper function to find a value in the JSON AST
std::string findValueInAST(const ASTNode &node, const std::string &key) {
    if (node.value == key) {
        return node.children.empty() ? "" : node.children[0].value;
    }
    for (const auto &child : node.children) {
        auto result = findValueInAST(child, key);
        if (!result.empty()) {
            return result;
        }
    }
    return "";
}

std::string CodeGen::generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot) {
    std::stringstream generatedCode;

    for (const auto &node : templateRoot.children) {
        if (node.type == TokenType::Placeholder) {
            std::string replacementValue = findValueInAST(dataRoot, node.value);
            generatedCode << (replacementValue.empty() ? node.value : replacementValue);
        } else {
            generatedCode << node.value;
        }
    }

    return generatedCode.str();
}