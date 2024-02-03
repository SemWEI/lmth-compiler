#include "parser.h"
#include "json.hpp"

ASTNode Parser::parse(const std::vector<Token> &tokens) {
    ASTNode root;
    for (const auto &token : tokens) {
        if (token.type != TokenType::EndOfFile) {
            root.children.push_back({token.type, token.value});
        }
    }
    return root;
}

ASTNode parseJSONObject(const json &jsonObj) {
    ASTNode node;
    node.type = TokenType::Identifier;  // Example type, adjust as needed
    node.value = jsonObj.value("name", "");

    if (jsonObj.contains("children")) {
        for (const auto &child : jsonObj["children"]) {
            node.children.push_back(parseJSONObject(child));
        }
    }

    return node;
}

ASTNode Parser::parseJSON(const std::string &jsonStr) {
    ASTNode root;

    // Parse the JSON string into a JSON object
    auto jsonObj = json::parse(jsonStr);

    // Assuming the root is a JSON object
    root = parseJSONObject(jsonObj);

    return root;
}