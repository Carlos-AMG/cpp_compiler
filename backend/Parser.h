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
    char op;
    ASTNode * right;

    BinaryOpNode(ASTNode * left, char op, ASTNode* right):
        left(left), op(op), right(right){}

};

struct NumberNode : public ASTNode {
    int value;
    NumberNode(int value) : value(value) {}
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