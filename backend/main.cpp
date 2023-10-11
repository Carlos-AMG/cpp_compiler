#include "Lexer.h"
#include "Parser.h"
#include <iostream>

void PrintAST(ASTNode* node, int indent = 0) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }

    if (dynamic_cast<BinaryOpNode*>(node)) {
        BinaryOpNode* binOpNode = dynamic_cast<BinaryOpNode*>(node);
        std::cout << "(";
        PrintAST(binOpNode->left);
        // std::cout << " " << binOpNode->op << " ";
        std::cout << " " << binOpNode->op_tok.lexeme << " ";
        PrintAST(binOpNode->right);
        std::cout << ")";
    } else if (dynamic_cast<NumberNode*>(node)) {
        NumberNode* numNode = dynamic_cast<NumberNode*>(node);
        std::string tokTypeStr = "";
        if (numNode->tok.type == TokenTypes::INT_LITERAL)
            tokTypeStr = "INT_LITERAL";
        else if (numNode->tok.type == TokenTypes::FLOAT_LITERAL)
            tokTypeStr = "FLOAT_LITERAL";
        std::cout << tokTypeStr << ":" << numNode->tok.lexeme << "";
    }
}

// Funcion que simplemente prueba la funcionalidad del Lexer (sin necesidad de bindings/gui)
int main(){
    Lexer lex1;
    // Parser pars1(lex1.tokens);
    std::string line;
    // std::string line = "x = a + b + c";
    std::cout << "Write some text: ";
    std::getline(std::cin, line);
    lex1.analyze(line);
    std::cout << "Tokens: " << std::endl;
    lex1.printTokens();

    Parser pars1(lex1.tokens);
    try {
        ASTNode* ast = pars1.parse();
        std::cout << "Abstract Syntax Tree (AST):" << std::endl;
        PrintAST(ast);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}