#ifndef __PARSER__
#define __PARSER__

#include <vector>
#include "Token.h"

// declaracion de clase Lexer la cual contiene una lista de tokens, la cual la funcion de analizar llenara con los respectivos tokens
// adicionalmente contiene las expresiones regulares para los diferentes tokens


struct NumberNode{
    Token token;
    NumberNode(Token token);
};

template <class A, class B, class C>
struct BinOpNode{
    A left_node;
    B op_tok;
    C right_node;
    BinOpNode(A left_node, B op_tok, C right_node){
        this->left_node = left_node;
        this->op_tok = op_tok;
        this->right_node = right_node;
    }
};

struct Parser{
    std::vector<Token> tokens;
    size_t tok_idx;
    Token curr_tok;
    Parser(const std::vector<Token> & inputTokens);

    Token advance();

    void parse(std::vector<Token> &tokens);

    NumberNode factor();
    void term();
    // void parse(const &std::vector<token> tokens);
};

#endif