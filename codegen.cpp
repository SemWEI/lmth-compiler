#include "codegen.h"
#include <sstream>
#include <unordered_map>

std::string CodeGen::generateFields(const ASTNode &fieldsNode) {
    std::stringstream fields;
    for (const auto &field : fieldsNode.children) {
        fields << field.value << ": " << field.children[0].value << ";\n";
    }
    return fields.str();
}

std::string CodeGen::replacePlaceholders(const std::string &templateStr, const ASTNode &dataNode) {
    std::string result = templateStr;

    for (const auto &child : dataNode.children) {
        std::string placeholder = "${" + child.value + "}";
        size_t pos = result.find(placeholder);
        if (pos != std::string::npos) {
            if (child.value == "FIELDS") {
                result.replace(pos, placeholder.length(), generateFields(child));
            } else {
                result.replace(pos, placeholder.length(), child.children[0].value);
            }
        }
    }

    return result;
}

std::string CodeGen::generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot) {
    std::stringstream generatedCode;

    for (const auto &node : templateRoot.children) {
        if (node.type == TokenType::Placeholder) {
            std::string replacementValue = replacePlaceholders(node.value, dataRoot);
            generatedCode << (replacementValue.empty() ? node.value : replacementValue);
        } else {
            generatedCode << node.value;
        }
    }

    return generatedCode.str();
}
