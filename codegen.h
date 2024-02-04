#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen {
public:
    std::string generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot);
    std::string replacePlaceholders(const std::string &templateStr, const ASTNode &dataNode);
    std::string generateFields(const ASTNode &fieldsNode);
    std::string generateMethods(const ASTNode &methodsNode);
    std::string generateRoutes(const ASTNode &componentsNode);
    std::string generateImports(const ASTNode &componentsNode, const std::string &type);
    std::string generateDeclarations(const ASTNode &componentsNode);
};

#endif
