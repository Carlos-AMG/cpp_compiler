#include "ASTVisitor.h"
#include "Token.h"

class SemanticAnalyzer : public ASTVisitor {
public:
    SymbolTable symbols;

    void visit(BinaryOpNode* node) override {
        // Visit the left and right nodes
        node->left->accept(*this);
        node->right->accept(*this);

        // Check if the operation is valid
        if (node->op_tok.type == TokenType::PLUS) {
            // The '+' operator requires both operands to be numbers
            if (symbols[node->left->value].type != Type::NUMBER ||
                symbols[node->right->value].type != Type::NUMBER) {
                throw TypeError("TypeError: '+' operator requires two numbers");
            }
        }
        // Add more checks for other operators...
    }

    void visit(NumberNode* node) override {
        // A number node doesn't have any children to visit,
        // but we can add its type to the symbol table
        symbols[node->value] = Symbol(Type::NUMBER);
    }

    // Add more visit methods for other node types...
};
