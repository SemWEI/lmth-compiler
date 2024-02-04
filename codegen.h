#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen {
public:
    std::string generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot);
    std::string replacePlaceholders(const std::string &templateStr, const ASTNode &dataNode);
    std::string generateFields(const ASTNode &fieldsNode);
};

#endif // CODEGEN_H
