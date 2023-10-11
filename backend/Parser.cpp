#include "Parser.h"
#include <iostream>



Parser::Parser(const std::vector<Token> & inputTokens): tokens{inputTokens}, curr_idx{0}{}

ASTNode* Parser::parse() {
    ASTNode* result = parseExpr();
    if (currentToken().type != TokenTypes::EOF_TOKEN) {
        throw std::runtime_error("Unexpected token after expression");
    }
    return result;
}


Token Parser::currentToken(){
    if (curr_idx < tokens.size()){
        return tokens[curr_idx];
    }
    return {TokenTypes::EOF_TOKEN, ""};
}

void Parser::advance(){
    curr_idx++;
}

ASTNode * Parser::parseExpr(){
    ASTNode * left = parseTerm();
    Token token = currentToken();
    while(currentToken().type == TokenTypes::ADDITION_OP || currentToken().type == TokenTypes::SUBTRACTION_OP){
        // char op = currentToken().lexeme[0];
        advance();
        ASTNode * right = parseTerm();
        // left = new BinaryOpNode(left, op, right);
        left = new BinaryOpNode(left, token, right);
    }
    return left;
}

ASTNode * Parser::parseTerm(){
    ASTNode * left = parseFactor();
    Token token = currentToken();
    while (currentToken().type == TokenTypes::MULTIPLICATION_OP || currentToken().type == TokenTypes::DIVISION_OP){
        // char op = currentToken().lexeme[0];
        advance();
        ASTNode * right = parseFactor();
        // left = new BinaryOpNode(left, op, right);
        left = new BinaryOpNode(left, token, right);
    }
    return left;
}

ASTNode* Parser::parseFactor() {
    Token token = currentToken();
    advance();
    if (token.type == TokenTypes::INT_LITERAL) {
        // return new NumberNode(std::stod(token.lexeme));
        return new NumberNode(token);
    } else if (token.type == TokenTypes::FLOAT_LITERAL) {
        // return new NumberNode(std::stod(token.lexeme));
        return new NumberNode(token);
    } else {
        throw std::runtime_error("Expected INT or FLOAT");
    }
}
