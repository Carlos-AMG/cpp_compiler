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

