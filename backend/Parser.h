#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include "Token.h"
#include <iostream>

// declaracion de clase Lexer la cual contiene una lista de tokens, la cual la funcion de analizar llenara con los respectivos tokens
// adicionalmente contiene las expresiones regulares para los diferentes tokens


struct ASTNode{
    virtual ~ASTNode() {}
};

struct BinaryOpNode: public ASTNode{
    ASTNode * left;
    Token op_tok;
    ASTNode * right;
    BinaryOpNode(ASTNode * left, Token rhs_op_tok, ASTNode * right): left{left}, op_tok{rhs_op_tok}, right{right}{}
};

struct UnaryOpNode : public ASTNode {
    Token op_tok;
    ASTNode* operand;
    UnaryOpNode(Token op_tok, ASTNode* operand) : op_tok(op_tok), operand(operand) {}
};

struct NumberNode : public ASTNode {
    Token tok;
    NumberNode(Token rhs_tok) : tok(rhs_tok) {}
};

struct AssignmentNode : public ASTNode {
    Token identifier;
    ASTNode* expression;
    AssignmentNode(const Token& identifier, ASTNode* expression)
        : identifier(identifier), expression(expression) {}
};

struct IdentifierNode : public ASTNode {
    Token identifier;
    IdentifierNode(const Token& identifier) : identifier(identifier) {}
};

struct StringNode : public ASTNode {
    Token string;
    StringNode(const Token& string) : string(string) {}
};
struct ReturnStatementNode : public ASTNode {
    ASTNode* expression;
    ReturnStatementNode(ASTNode* expression) : expression(expression) {}

    ~ReturnStatementNode() {
        delete expression;
    }
};

struct ProgramNode: public ASTNode {
    std::vector<ASTNode*> statements;

    ProgramNode(const std::vector<ASTNode*>& statements) : statements(statements) {}

    ~ProgramNode() {
        for (ASTNode* statement : statements) {
            delete statement;
        }
    }
};

struct IfStatementNode : public ASTNode {
    ASTNode* condition;
    ASTNode* if_body;
    ASTNode* else_body;

    IfStatementNode(ASTNode* condition, ASTNode* if_body, ASTNode* else_body = nullptr)
        : condition(condition), if_body(if_body), else_body(else_body) {}

    ~IfStatementNode() {
        delete condition;
        delete if_body;
        if (else_body != nullptr) {
            delete else_body;
        }
    }
};


struct Parser{
    std::vector<Token> tokens;
    size_t curr_idx;

    Token currentToken();
    void advance();
    //ASTNode * parseProgram();
    ASTNode* parseProgram();
    ASTNode* parseStatement();
    ASTNode* parseAssignment();
    ASTNode* parseExpression();
    ASTNode* parseLogicalOr();
    ASTNode* parseLogicalAnd();
    ASTNode* parseEquality();
    ASTNode* parseRelational();
    ASTNode* parseAdditive();
    ASTNode* parseMultiplicative();
    ASTNode* parseUnary();
    ASTNode* parsePrimary();
    ASTNode* parseReturnStatement();
    ASTNode* parseIfStatement();
    ASTNode* parseBlock();

    Token peek();
    Parser(const std::vector<Token> & inputTokens);
};

#endif