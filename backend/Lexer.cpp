#include "Lexer.h"
#include "utils/utils.h"
#include <iostream>
#include <regex>
#include <unordered_map>

// Definimos e inicializamos las expresiones regulares de los tokens
const std::regex Lexer::identifierRegex("[a-zA-Z][a-zA-Z0-9]*");
const std::regex Lexer::integerRegex("[0-9]+");
const std::regex Lexer::floatRegex("[0-9]+\\.[0-9]+");
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
// const std::regex Lexer::reservedWordsRegex("if|while|return|else|int|float");
const std::regex Lexer::ifRegex("if");
const std::regex Lexer::elseRegex("else");
const std::regex Lexer::whileRegex("while");
const std::regex Lexer::reservedIntRegex("int");
const std::regex Lexer::reservedFloatRegex("float");




const std::regex Lexer::binaryOperatorsRegex("[,!=%&*+-\\/-><<==>>=^|]+");
const std::regex Lexer::unaryOperatorsRegex("[-!]|\\+\\+|--");

// Funcion encargada de analizar una cadena y usando las expresiones regulares debe guardar los tokens en una lista
// de tokens. Itera sobre la cadena y compara las expresiones para asi saber a que token pertenece
int Lexer::analyze(std::string line) {
    int resultingTokens = 0;
    std::string lexeme;
    TokenTypes type;
    std::string delimiters = "=-+/";
    std::string whitespaces = " \n\t";
    int line_length = line.length();

    std::unordered_map<const std::regex*, TokenTypes> regexToTokenTypeMap = {
        {&identifierRegex, TokenTypes::IDENTIFIER},
        {&integerRegex, TokenTypes::INT_LITERAL},
        {&floatRegex, TokenTypes::FLOAT_LITERAL},
        {&leftParenthesisRegex, TokenTypes::LEFT_PAREN},
        {&rightParenthesisRegex, TokenTypes::RIGHT_PAREN},
        {&leftBraceRegex, TokenTypes::LEFT_BRACKET},
        {&rightBraceRegex, TokenTypes::RIGHT_BRACKET},
        {&ifRegex, TokenTypes::IF}
    };

    for (int i = 0; i < line_length;){
        lexeme = "";
        // Skip whitespace characters
       while (i < line_length && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) {
            i++;
        }

        // Operators
        if (i < line_length && 
            std::regex_match(std::string(1, line[i]), binaryOperatorsRegex) || 
            std::regex_match(std::string(1, line[i]), unaryOperatorsRegex)){
                lexeme += line[i];
                // Set the appropriate token type based on the matched operator
                switch (line[i])
                {
                    case '+':
                        type = TokenTypes::ADDITION_OP;
                        if (line[i+1] == '+'){
                            lexeme += line[++i];
                            type = TokenTypes::PLUS_PLUS_OP;
                        }
                        break;
                    case '-':
                        type = TokenTypes::SUBTRACTION_OP; 
                        if (line[i+1] == '-'){
                            lexeme += line[i++];
                            type = TokenTypes::MINUS_MINUS_OP;
                        }              
                        break;
                    case '=':
                        type = TokenTypes::ASSIGNMENT_OP;
                        if (line[i+1] == '='){
                            lexeme += line[i++];
                            type = TokenTypes::EQUALITY_OP;
                        }     
                        break; 
                    case '/':
                        type = TokenTypes::DIVISION_OP;
                        break;
                    case '*':
                        type = TokenTypes::MULTIPLICATION_OP;
                        break; 
                    case '>':
                        type = TokenTypes::MORE_THAN_OP;
                        break;
                    case '<':
                        type = TokenTypes::LESS_THAN_OP;
                        break;
                    case '!':
                        type = TokenTypes::NOT_OP;
                        if (line[i+1] == '='){
                            lexeme += line[++i];
                            type = TokenTypes::INEQUALITY_OP;
                        } 
                        break;
                      
                }
                i++;
                tokens.push_back(Token(type, lexeme));
                continue;
        }
        if (i < line_length && 
            std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
            std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
            std::regex_match(std::string(1, line[i]), leftParenthesisRegex) || 
            std::regex_match(std::string(1, line[i]), rightParenthesisRegex) ){
            lexeme += line[i];

            switch (line[i])
                {
                    case '{':
                        type = TokenTypes::LEFT_BRACKET;
                        break;
                    case '}':
                        type = TokenTypes::RIGHT_BRACKET;        
                        break;  
                    case '(':
                        type = TokenTypes::LEFT_PAREN;
                        break;
                    case ')':
                        type = TokenTypes::RIGHT_PAREN;        
                        break;  
                }
                i++;
                tokens.push_back(Token(type, lexeme));
                continue;
        }
        // Continue building the lexeme until a delimiter is encountered
        while (i < line_length && whitespaces.find(line[i]) == std::string::npos && delimiters.find(line[i]) == std::string::npos ) {
            lexeme += line[i];
            i++;
        }
        // Determine the token type based on the lexeme content using the map
        for (const auto& regexPair : regexToTokenTypeMap) {
            if (!lexeme.empty() && std::regex_match(lexeme, *(regexPair.first))) { // Compare lexeme to the pattern
                type = regexPair.second;
                break;
            }
        }
        if (!lexeme.empty()){
            tokens.push_back(Token(type, lexeme));
            resultingTokens++;
        }
    }
    tokens.push_back(Token(TokenTypes::EOF_TOKEN, ""));
    return resultingTokens;
}


void Lexer::printTokens(){
    std::string typeName;
    for (auto token : this->tokens){
        typeName = tokenTypeToString(token.type);
        std::cout << "Type: " << typeName << ", Lexeme: " <<  token.lexeme << std::endl;
    }
}

// std::vector<Token> Lexer::getTokens(){
//     return this->tokens;
// }
