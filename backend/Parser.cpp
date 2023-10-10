#include "Parser.h"
#include <iostream>


NumberNode::NumberNode(Token token): token{token}{}

// NumberNode::NumberNode(Token token){
//     this->token = token;
// }


Parser::Parser(const std::vector<Token> & inputTokens): tokens{inputTokens}, tok_idx {1}{}


void Parser::parse(std::vector<Token> &tokens){
    
    while (!tokens.empty())
    {
        Token curr_token = tokens.back();
        tokens.pop_back();
        std::cout << curr_token.lexeme << std::endl;
        if (curr_token.lexeme == "123"){
            NumberNode number(curr_token);
        }
    }
    
}

Token Parser::advance(){
    tok_idx += 1;
    if (tok_idx < tokens.size()){
        this->curr_tok = tokens[tok_idx];
        return tokens[tok_idx];
    }
}

NumberNode Parser::factor(){
    
    Token token = curr_tok;
    if (token.type == TokenTypes::INT_LITERAL || token.type == TokenTypes::FLOAT_LITERAL){
        advance();
        return NumberNode(token);
    }
}
void Parser::term(){
    NumberNode left = factor();
    while (curr_tok.type == TokenTypes::MULTIPLICATION_OP or curr_tok.type == TokenTypes::DIVISION_OP){
        Token op_tok = curr_tok;
        NumberNode right = factor();
        BinOpNode left = BinOpNode(left, op_tok, right);
    }
    return left
}

// void Parser::term(Token token){
//     Token left = token;
//     while (token)
// }