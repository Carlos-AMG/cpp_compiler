#include "Parser.h"

class ASTVisitor {
public:
    virtual ~ASTVisitor() {}

    virtual void visit(BinaryOpNode* node) = 0;
    virtual void visit(UnaryOpNode* node) = 0;
    virtual void visit(NumberNode* node) = 0;
    virtual void visit(AssignmentNode* node) = 0;
    virtual void visit(IdentifierNode* node) = 0;
    virtual void visit(StringNode* node) = 0;
    virtual void visit(ReturnStatementNode* node) = 0;
    virtual void visit(ProgramNode* node) = 0;
    virtual void visit(IfStatementNode* node) = 0;
    // Add more visit methods for other node types...
};
