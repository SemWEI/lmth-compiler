class CodeGen {
public:
    std::string generateCode(const ASTNode &templateRoot, const ASTNode &dataRoot);
    std::string replacePlaceholders(const std::string &templateStr, const ASTNode &dataNode);
    std::string generateFields(const ASTNode &fieldsNode);
    std::string generateMethods(const ASTNode &methodsNode);
    std::string generateRoutes(const ASTNode &componentsNode);
    std::string generateImports(const ASTNode &componentsNode, const std::string &type);
    std::string generateDeclarations(const ASTNode &componentsNode);

    // Backend specific
    std::string generateRouteHandlers(const ASTNode &controllerNode);
    std::string generateControllerMethods(const ASTNode &methodsNode);
    std::string generateServiceMethods(const ASTNode &methodsNode);
};