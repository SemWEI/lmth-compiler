#include "codegen.h"
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Verifier.h>

void CodeGen::generateCode(const ASTNode &root) {
    llvm::LLVMContext context;
    llvm::Module module("toy_module", context);
    llvm::IRBuilder<> builder(context);

    // Implement code generation logic
    // Generate LLVM IR using the IRBuilder

    module.print(llvm::outs(), nullptr);
}
