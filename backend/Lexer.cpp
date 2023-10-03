#include "Lexer.h"
#include "utils/utils.h"
#include <iostream>
#include <regex>


// Definimos e inicializamos las expresiones regulares de los tokens
const std::regex Lexer::identifierRegex("[a-zA-Z][a-zA-Z0-9]*");
const std::regex Lexer::integerRegex("[0-9]+");
const std::regex Lexer::realRegex("[0-9]+\\.[0-9]+");
const std::regex Lexer::stringRegex("\"[^\"]*\"");
const std::regex Lexer::additionOperatorRegex("[\\+\\-]");
const std::regex Lexer::multiplicationOperatorRegex("[\\*/]");
const std::regex Lexer::assignmentOperatorRegex("=");
const std::regex Lexer::relationalOperatorRegex("[<>]=?|!=|==");
const std::regex Lexer::logicalAndOperatorRegex("&");
const std::regex Lexer::logicalOrOperatorRegex("\\|");
const std::regex Lexer::logicalNotOperatorRegex("!");
const std::regex Lexer::leftParenthesisRegex("\\(");
const std::regex Lexer::rightParenthesisRegex("\\)");
const std::regex Lexer::leftBraceRegex("\\{");
const std::regex Lexer::rightBraceRegex("\\}");
const std::regex Lexer::semicolonRegex(";");
const std::regex Lexer::reservedWordsRegex("if|while|return|else|int|float");


// Funcion encargada de analizar una cadena y usando las expresiones regulares debe guardar los tokens en una lista
// de tokens. Itera sobre la cadena y compara las expresiones para asi saber a que token pertenece
int Lexer::analyze(std::string line) {
    std::string lexeme = "";
    for (int i = 0; i < line.length(); i++){
        if (line[i] == ' ')
            continue;
        for (int j = i; j < )
    }
    
    return resultingTokens;
}


void Lexer::printTokens(){
    for (auto token : this->tokens){
        std::cout << "Token: " << token.name << ", Lexeme: " << token.value << std::endl;
    }
}

std::vector<Token> Lexer::getTokens(){
    return this->tokens;
}
