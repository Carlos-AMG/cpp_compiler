#include "utils.h"
#include <fstream>
#include <sstream>

bool isOperator(char character){
    return (character == '+' || character == '-' || character == '*' || character == '/');
}

std::string readFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}

std::vector<std::string> readLinesFromFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::vector<std::string> lines;
    std::string line;

    while (std::getline(inFile, line)) {
        lines.push_back(line);
    }

    return lines;
}

// Function to convert TokenTypes to string
std::string tokenTypeToString(TokenTypes type) {
    switch (type)
        {
        case TokenTypes::IDENTIFIER:
            return "IDENTIFIER";
        case TokenTypes::INEQUALITY_OP:
            return "INEQUALITY_OP";
        case TokenTypes::MORE_THAN_OP:
            return "MORE_THAN_OP";
        case TokenTypes::LESS_THAN_OP:
            return "LESS_THAN_OP";
        case TokenTypes::ADDITION_OP:
            return "ADDITION_OP";
        case TokenTypes::ASSIGNMENT_OP:
            return "ASSIGNMENT_OP";
        case TokenTypes::SUBTRACTION_OP:
            return "SUBTRACTION_OP";
        case TokenTypes::MULTIPLICATION_OP:
            return "MULTIPLICATION_OP";
        case TokenTypes::DIVISION_OP:
            return "DIVISION_OP";
        case TokenTypes::PLUS_PLUS_OP:
            return "PLUS_PLUS_OP";
        case TokenTypes:: MINUS_MINUS_OP:
            return "MINUS_MINUS_OP";
        case TokenTypes::INT_LITERAL:
            return "INT_LITERAL";
        case TokenTypes::FLOAT_LITERAL:
            return "FLOAT_LITERAL";
        case TokenTypes::IF:
            return "IF";
        case TokenTypes::ELSE:
            return "ELSE";
        case TokenTypes::RETURN:
            return "RETURN";
        case TokenTypes::SEMICOLON:
            return "SEMICOLON";
        case TokenTypes::LEFT_PAREN:
            return "LEFT_PAREN";
        case TokenTypes::RIGHT_PAREN:
            return "RIGHT_PAREN";
        case TokenTypes::LEFT_BRACKET:
            return "LEFT_BRACKET";
        case TokenTypes::RIGHT_BRACKET:
            return "RIGHT_BRACKET";
        case TokenTypes::EOF_TOKEN:
            return "EOF";
        case TokenTypes::FLOAT:
            return "FLOAT";
        case TokenTypes::INTEGER:
            return "INTEGER";
        case TokenTypes::STRING_LITERAL:
            return "STRING_LITERAL";
        default:
            break;
        }
}  


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
    } else if (dynamic_cast<StringNode*> (node)){
        StringNode* strNode = dynamic_cast<StringNode*>(node);
        std::cout << "String literal: " << strNode->string.lexeme << std::endl; 
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