#include "codegen.h"
#include <sstream>
#include <unordered_map>

// Generate Route Handlers
std::string CodeGen::generateRouteHandlers(const ASTNode &controllerNode) {
    std::stringstream handlers;
    for (const auto &method : controllerNode.children) {
        handlers << "router." << method.children[1].value << "('"
                 << method.children[0].value << "', "
                 << controllerNode.value << "."
                 << method.value << ");\n";
    }
    return handlers.str();
}

// Generate Controller Methods
std::string CodeGen::generateControllerMethods(const ASTNode &methodsNode) {
    std::stringstream methods;
    for (const auto &method : methodsNode.children) {
        methods << method.value << "(req, res) {\n"
                << "  // Implement " << method.value << " logic here\n"
                << "  res.json(" << method.value << ");\n"
                << "}\n\n";
    }
    return methods.str();
}

// Generate Service Methods
std::string CodeGen::generateServiceMethods(const ASTNode &methodsNode) {
    std::stringstream methods;
    for (const auto &method : methodsNode.children) {
        methods << method.value << "("
                << (method.children.size() > 1 ? method.children[1].value : "")
                << ") {\n"
                << "  // Implement " << method.value << " logic here\n"
                << "  return [];\n"
                << "}\n\n";
    }
    return methods.str();
}

// Generate Fields
std::string CodeGen::generateFields(const ASTNode &fieldsNode) {
    std::stringstream fields;
    for (const auto &field : fieldsNode.children) {
        fields << field.value << ": " << field.children[0].value << ";\n";
    }
    return fields.str();
}

// Generate Methods
std::string CodeGen::generateMethods(const ASTNode &methodsNode) {
    std::stringstream methods;
    for (const auto &method : methodsNode.children) {
        methods << method.value << "(): " << method.children[0].value
                << " {\n  return this.http.get<" << method.children[0].value
                << ">(`" << method.children[1].value << "`);\n}\n\n";
    }
    return methods.str();
}

// Generate Routes
std::string CodeGen::generateRoutes(const ASTNode &componentsNode) {
    std::stringstream routes;
    for (const auto &component : componentsNode.children) {
        routes << "{ path: '" << component.children[3].value << "', component: "
               << component.value << "Component },\n";
    }
    return routes.str();
}

// Generate Imports
std::string CodeGen::generateImports(const ASTNode &componentsNode, const std::string &type) {
    std::stringstream imports;
    for (const auto &component : componentsNode.children) {
        if (type == "component") {
            imports << "import { " << component.value << "Component } from './"
                    << component.value << ".component';\n";
        } else if (type == "service") {
            imports << "import { " << component.value << "Service } from './services/"
                    << component.value << ".service';\n";
        }
    }
    return imports.str();
}

// Generate Declarations
std::string CodeGen::generateDeclarations(const ASTNode &componentsNode) {
    std::stringstream declarations;
    for (const auto &component : componentsNode.children) {
        declarations << component.value << "Component,\n";
    }
    return declarations.str();
}

// Replace Placeholders
std::string CodeGen::replacePlaceholders(const std::string &templateStr, const ASTNode &dataNode) {
    std::string result = templateStr;

    for (const auto &child : dataNode.children) {
        std::string placeholder = "${" + child.value + "}";
        size_t pos = result.find(placeholder);
        if (pos != std::string::npos) {
            if (child.value == "FIELDS") {
                result.replace(pos, placeholder.length(), generateFields(child));
            } else if (child.value == "METHOD_IMPLEMENTATIONS") {
                if (child.parent->value == "controller") {
                    result.replace(pos, placeholder.length(), generateControllerMethods(child));
                } else if (child.parent->value == "service") {
                    result.replace(pos, placeholder.length(), generateServiceMethods(child));
                } else {
                    result.replace(pos, placeholder.length(), generateMethods(child));
                }
            } else if (child.value == "ROUTES") {
                result.replace(pos, placeholder.length(), generateRoutes(child));
            } else if (child.value == "IMPORT_COMPONENTS") {
                result.replace(pos, placeholder.length(), generateImports(child, "component"));
            } else if (child.value == "IMPORT_SERVICES") {
                result.replace(pos, placeholder.length(), generateImports(child, "service"));
            } else if (child.value == "DECLARATIONS") {
                result.replace(pos, placeholder.length(), generateDeclarations(child));
            } else if (child.value == "ROUTE_HANDLERS") {
                result.replace(pos, placeholder.length(), generateRouteHandlers(child));
            } else {
                result.replace(pos, placeholder.length(), child.children[0].value);
            }
        }
    }

    return result;
}

// Generate Code
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