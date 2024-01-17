#include "codegen.h"
#include <sstream>
#include <unordered_map>

std::string replacePlaceholder(const std::string &placeholder) {
    static std::unordered_map<std::string, std::string> replacements = {
        {"PLACEHOLDER_NAME", "ReplacedName"},
        {"PLACEHOLDER_TYPE", "ReplacedType"}
    };

    auto it = replacements.find(placeholder);
    if (it != replacements.end()) {
        return it->second;
    }
    return placeholder; // If no replacement found, return the original
}

std::string CodeGen::generateCode(const ASTNode &root) {
    std::stringstream generatedCode;

    for (const auto &node : root.children) {
        if (node.type == TokenType::Placeholder) {
            generatedCode << replacePlaceholder(node.value);
        } else {
            generatedCode << node.value;
        }
    }

    return generatedCode.str();
}