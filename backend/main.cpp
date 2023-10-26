#include "Lexer.h"
#include "Parser.h"
#include "utils/utils.h"
#include <string>
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
        std::cout << "Binary Operation: " << binOpNode->op_tok.lexeme << std::endl;
        PrintAST(binOpNode->left, indent + 1);
        PrintAST(binOpNode->right, indent + 1);
    } else if (dynamic_cast<UnaryOpNode*>(node)) {
        UnaryOpNode* unaryNode = dynamic_cast<UnaryOpNode*>(node);
        std::cout << "Unary Operation: " << unaryNode->op_tok.lexeme << std::endl;
        PrintAST(unaryNode->operand, indent + 1);
    } else if (dynamic_cast<NumberNode*>(node)) {
        NumberNode* numNode = dynamic_cast<NumberNode*>(node);
        std::string tokTypeStr = "";
        if (numNode->tok.type == TokenTypes::INT_LITERAL) {
            tokTypeStr = "INT_LITERAL";
        } else if (numNode->tok.type == TokenTypes::FLOAT_LITERAL) {
            tokTypeStr = "FLOAT_LITERAL";
        }
        std::cout << "Number: " << tokTypeStr << " - " << numNode->tok.lexeme << std::endl;
    } else if (dynamic_cast<AssignmentNode*>(node)) {
        AssignmentNode* assignmentNode = dynamic_cast<AssignmentNode*>(node);
        std::cout << "Assignment: " << assignmentNode->identifier.lexeme << std::endl;
        PrintAST(assignmentNode->expression, indent + 1);
    } else if (dynamic_cast<IdentifierNode*>(node)) {
        IdentifierNode* idNode = dynamic_cast<IdentifierNode*>(node);
        std::cout << "Identifier: " << idNode->identifier.lexeme << std::endl;
    } else if (dynamic_cast<ReturnStatementNode*>(node)) {
        ReturnStatementNode* returnNode = dynamic_cast<ReturnStatementNode*>(node);
        std::cout << "Return Statement" << std::endl;
        PrintAST(returnNode->expression, indent + 1);
    } else if (dynamic_cast<IfStatementNode*>(node)) {
        IfStatementNode* ifNode = dynamic_cast<IfStatementNode*>(node);
        std::cout << "If Statement" << std::endl;
        std::cout << "Condition:" << std::endl;
        PrintAST(ifNode->condition, indent + 1);
        std::cout << "If Body:" << std::endl;
        PrintAST(ifNode->if_body, indent + 1);
        if (ifNode->else_body != nullptr) {
            std::cout << "Else Body:" << std::endl;
            PrintAST(ifNode->else_body, indent + 1);
        }
    } else if (dynamic_cast<ProgramNode*>(node)) {
        ProgramNode* programNode = dynamic_cast<ProgramNode*>(node);
        std::cout << "Program:" << std::endl;
        for (ASTNode* statement : programNode->statements) {
            PrintAST(statement, indent + 1);
        }
    }
}


// Funcion que simplemente prueba la funcionalidad del Lexer (sin necesidad de bindings/gui)
int main(){
    Lexer lex1;

    // std::vector<std::string> lines;
    std::string text;
    try {
        text = readFile("./text.txt");
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Lexer lex;
    lex.analyze(text);
    Parser pars(lex.tokens);
    lex.printTokens();

    try {
        ASTNode* ast = pars.parseProgram();
        PrintAST(ast);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    
    // size_t line = 0;
    // for (auto line: lines){
    //     Lexer lex1;
    //     lex1.analyze(line);
    //     Parser pars1(lex1.tokens);
    //     std::cout << "lexer input: " << line << std::endl;
    //     std::cout << "Tokens: " << std::endl;
    //     lex1.printTokens();
    //     try {
    //         ASTNode* ast = pars1.parseProgram();
    //         std::cout << "Abstract Syntax Tree (AST):" << std::endl;
    //         PrintAST(ast);
    //     } catch (const std::exception& e) {
    //         std::cerr << "Error on line: " << line << ":"<< e.what() << std::endl;
    //     }
    //     line += 1;
    // }
    return 0;
}