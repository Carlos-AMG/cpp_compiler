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
    // char op;
    Token op_tok;
    ASTNode * right;
    BinaryOpNode(ASTNode * left, Token rhs_op_tok, ASTNode * right): left{left}, op_tok{rhs_op_tok}, right{right}{}

    // BinaryOpNode(ASTNode * left, char op, ASTNode* right):
    //     left(left), op(op), right(right){}
};

struct NumberNode : public ASTNode {
    // int value;
    Token tok;
    // NumberNode(int value) : value(value) {}
    NumberNode(Token rhs_tok) : tok(rhs_tok) {}
};

struct Parser{
    std::vector<Token> tokens;
    size_t curr_idx;

    Token currentToken();
    void advance();
    ASTNode * parse();
    ASTNode * parseExpr(); 
    ASTNode * parseTerm();
    ASTNode * parseFactor();
    
    Parser(const std::vector<Token> & inputTokens);
};

#endif