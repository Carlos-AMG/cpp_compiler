#include "Lexer.h"
#include "Parser.h"
#include "utils/utils.h"
#include "SymbolTable.h"
#include <string>
#include <iostream>

bool error = false; 

Token validateTree(ASTNode* node, SymbolTable& table) {
    if (node == nullptr) {
        return Token(TokenTypes::NULLT, "null");
    }

    if (auto binOpNode = dynamic_cast<BinaryOpNode*>(node)) {
        auto lhs = validateTree(binOpNode->left, table);
        auto rhs = validateTree(binOpNode->right, table);

        Symbol temp;
        if (lhs.type == TokenTypes::IDENTIFIER){
            temp = table.lookup(lhs.lexeme);
            lhs.type = temp.type;         
        }
        if (rhs.type == TokenTypes::IDENTIFIER){
            temp = table.lookup(rhs.lexeme);
            rhs.type = temp.type;  
        }

        if (binOpNode->op_tok.type == TokenTypes::DIVISION_OP && rhs.lexeme == "0") {
            std::cout << "Error: División entre cero, en la línea: " << binOpNode->op_tok.lineNumber << std::endl;
            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("División entre cero");
        }

        if (lhs.type != rhs.type) {
            std::cout << "Error: Tipos incompatibles en la línea: " << binOpNode->op_tok.lineNumber << std::endl;
            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("Tipos incompatibles");
        }

        return lhs;  // Podrías devolver rhs si ambos deben ser iguales
    } else if (auto unaryNode = dynamic_cast<UnaryOpNode*>(node)) {
        validateTree(unaryNode->operand, table);
    } else if (auto numNode = dynamic_cast<NumberNode*>(node)) {
        return numNode->tok;
    } else if (auto assignmentNode = dynamic_cast<AssignmentNode*>(node)) { // x = 1
        auto lhs = assignmentNode->identifier;
        auto rhs = validateTree(assignmentNode->expression, table);
        table.insert(lhs.lexeme, rhs.type);
        validateTree(assignmentNode->expression, table);
    } else if (auto strNode = dynamic_cast<StringNode*>(node)){
        return strNode->string;
    } else if (auto idNode = dynamic_cast<IdentifierNode*>(node)) {
        auto identifier = table.lookup(idNode->identifier.lexeme);
        if (identifier.type == TokenTypes::NULLT) {
            std::cout << "Error: Variable no declarada: " << idNode->identifier.lexeme << " en la línea: " << idNode->identifier.lineNumber << std::endl;
            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("Variable no declarada");
        }
        return(idNode->identifier);
    } else if (auto returnNode = dynamic_cast<ReturnStatementNode*>(node)) {
        validateTree(returnNode->expression, table);
    } else if (auto ifNode = dynamic_cast<IfStatementNode*>(node)) {
        validateTree(ifNode->condition, table);
        validateTree(ifNode->if_body, table);
        if (ifNode->else_body != nullptr) {
            validateTree(ifNode->else_body, table);
        }
    } else if (auto programNode = dynamic_cast<ProgramNode*>(node)) {
        for (ASTNode* statement : programNode->statements) {
            validateTree(statement, table);
        }
    }

    return Token();  // Otra opción es devolver un token nulo por defecto
}

void printAst(ASTNode* node, SymbolTable & table, int indent = 0) {
    if (node == nullptr) {
        return;
    }

    for (int i = 0; i < indent; ++i) {
        std::cout << "  ";
    }

    if (dynamic_cast<BinaryOpNode*>(node)) {
        BinaryOpNode* binOpNode = dynamic_cast<BinaryOpNode*>(node);
        std::cout << "Binary Operation: " << binOpNode->op_tok.lexeme << std::endl;
        // auto lhs = dynamic_cast<NumberNode*>(binOpNode->left)->tok;
        // auto opTok = binOpNode->op_tok;
        // auto rhs = dynamic_cast<NumberNode*>(binOpNode->right)->tok;
        // if (opTok.type == TokenTypes::DIVISION_OP && rhs.lexeme == "0"){
        //     throw std::runtime_error("division entre cero");
        // }

        printAst(binOpNode->left, table, indent + 1);
        printAst(binOpNode->right, table, indent + 1);
    } else if (dynamic_cast<UnaryOpNode*>(node)) {
        UnaryOpNode* unaryNode = dynamic_cast<UnaryOpNode*>(node);
        std::cout << "Unary Operation: " << unaryNode->op_tok.lexeme << std::endl;
        printAst(unaryNode->operand, table, indent + 1);
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
        auto lhs = assignmentNode->identifier;
        table.insert(lhs.lexeme, lhs.type);
        printAst(assignmentNode->expression, table, indent + 1);
    } else if (dynamic_cast<IdentifierNode*>(node)) {
        IdentifierNode* idNode = dynamic_cast<IdentifierNode*>(node);
        auto identifier = table.lookup(idNode->identifier.lexeme);
        if (identifier.type == TokenTypes::NULLT){
            throw std::runtime_error("variable no declarada");
        }
        std::cout << "Identifier: " << idNode->identifier.lexeme << std::endl;
    } else if (dynamic_cast<StringNode*> (node)){
        StringNode* strNode = dynamic_cast<StringNode*>(node);
        std::cout << "String literal: " << strNode->string.lexeme << std::endl; 
    } else if (dynamic_cast<ReturnStatementNode*>(node)) {
        ReturnStatementNode* returnNode = dynamic_cast<ReturnStatementNode*>(node);
        std::cout << "Return Statement" << std::endl;
        printAst(returnNode->expression, table, indent + 1);
    } else if (dynamic_cast<IfStatementNode*>(node)) {
        IfStatementNode* ifNode = dynamic_cast<IfStatementNode*>(node);
        std::cout << "If Statement" << std::endl;
        std::cout << "Condition:" << std::endl;
        printAst(ifNode->condition, table, indent + 1);
        std::cout << "If Body:" << std::endl;
        printAst(ifNode->if_body, table, indent + 1);
        if (ifNode->else_body != nullptr) {
            std::cout << "Else Body:" << std::endl;
            printAst(ifNode->else_body, table, indent + 1);
        }
    } else if (dynamic_cast<ProgramNode*>(node)) {
        ProgramNode* programNode = dynamic_cast<ProgramNode*>(node);
        for (ASTNode* statement : programNode->statements) {
            printAst(statement, table,  indent + 1);
        }
    }
}



int main(){
    Lexer lex1;
    SymbolTable table1;

    std::string text;
    try {
        text = readFile("./text.txt");
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Lexer lex;
    try {
        lex.analyze(text);
        // lex.printTokens();
        Parser pars (lex.tokens);
        auto tree = pars.parseProgram();
        // printAst(tree, table1);
        validateTree(tree, table1);
        if (error){
            throw std::runtime_error("");
        }
        std::cout << "valido" << std::endl;
    } catch (const std::exception& e){
        std::cerr << "Error" << e.what() << std::endl;
    }
    
    for (const auto& pair : table1.symbols) {
        std::cout << "Lexeme: " << pair.first << ", Type: " << tokenTypeToString(pair.second.type) << std::endl;
    }

    return 0;
}