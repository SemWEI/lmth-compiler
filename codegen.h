#ifndef CODEGEN_H
#define CODEGEN_H

#include "parser.h"

class CodeGen {
public:
    void generateCode(const ASTNode &root);
};

#endif // CODEGEN_H