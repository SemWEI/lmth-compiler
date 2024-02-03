#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen {
public:
    std::string generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot);
};

#endif // CODEGEN_H