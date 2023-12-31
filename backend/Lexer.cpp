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
const std::regex Lexer::reservedReturn("return");

const std::regex Lexer::binaryOperatorsRegex("[,!=%&*+-\\/-><<==>>=^|]+");
const std::regex Lexer::unaryOperatorsRegex("[-!]|\\+\\+|--");

// Funcion encargada de analizar una cadena y usando las expresiones regulares debe guardar los tokens en una lista
// de tokens. Itera sobre la cadena y compara las expresiones para asi saber a que token pertenece
int Lexer::analyze(std::string line) {
    size_t lineNumber = 1;
    int resultingTokens = 0;
    std::string lexeme;
    TokenTypes type;
    std::string delimiters = "=-+/";
    std::string delimiters2 = "{";
    std::string whitespaces = " \n\t";
    int line_length = line.length();

    std::unordered_map<const std::regex*, TokenTypes> regexToTokenTypeMap = {
        {&integerRegex, TokenTypes::INT_LITERAL},
        {&floatRegex, TokenTypes::FLOAT_LITERAL},
        {&leftParenthesisRegex, TokenTypes::LEFT_PAREN},
        {&rightParenthesisRegex, TokenTypes::RIGHT_PAREN},
        {&reservedReturn, TokenTypes::RETURN},        
        {&leftBraceRegex, TokenTypes::LEFT_BRACKET},
        {&rightBraceRegex, TokenTypes::RIGHT_BRACKET},
        {&ifRegex, TokenTypes::IF},
        {&identifierRegex, TokenTypes::IDENTIFIER},
        {&reservedIntRegex, TokenTypes::INTEGER},
        {&reservedFloatRegex, TokenTypes::FLOAT}
        // {&stringRegex, TokenTypes::STRING_LITERAL}
    };
    

    for (int i = 0; i < line_length;){
        lexeme = "";
        // Skip whitespace characters
        if (line[i] == '\n'){
            lineNumber += 1;
        }
       while (i < line_length && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) {
            i++;
        }

        // size_t start = 0;
        // if (line[i] == '\"'){
        //     while ((start = line.find('\"', start)) != std::string::npos) {
        //         size_t end = line.find('\"', start + 1);
        //         if (end == std::string::npos) {
        //             std::cerr << "Error: String no cerrado correctamente." << std::endl;
        //             break;
        //         }
        //         std::string extractedString = line.substr(start + 1, end - start - 1);
        //         lexeme += extractedString;
        //         start = end + 1;
        //     }
        //     tokens.push_back(Token(TokenTypes::STRING_LITERAL, lexeme, lineNumber));
        //     continue;
        // }


        if (line[i] == '\"') {
            lexeme += line[i];
            i++;
            while (i < line_length && line[i] != '\"') {
                lexeme += line[i];
                i++;
            }
            if (i < line_length && line[i] == '\"') {
                lexeme += line[i];
                i++;
                tokens.push_back(Token(TokenTypes::STRING_LITERAL, lexeme, lineNumber));
                continue;
            } else {
                throw std::runtime_error("Error en la línea " + std::to_string(lineNumber) + ": String literal no cerrado");
            }
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
                tokens.push_back(Token(type, lexeme, lineNumber));
                continue;
        }
        if (i < line_length && 
            std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
            std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
            std::regex_match(std::string(1, line[i]), leftParenthesisRegex) || 
            std::regex_match(std::string(1, line[i]), rightParenthesisRegex) ||
            line[i] == ';'){
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
                    case ';':
                        type = TokenTypes::SEMICOLON;        
                        break;  
                }
                i++;
                tokens.push_back(Token(type, lexeme, lineNumber));
                continue;
        }
        // Continue building the lexeme until a delimiter is encountered
        while (i < line_length && whitespaces.find(line[i]) == std::string::npos && delimiters.find(line[i]) == std::string::npos) {
            lexeme += line[i];
            i++;
        }
        // Determine the token type based on the lexeme content using the map
        bool match = false;
        for (const auto& regexPair : regexToTokenTypeMap) {
            if (!lexeme.empty() && std::regex_match(lexeme, *(regexPair.first))) { // Compare lexeme to the pattern
                match = true;
                type = regexPair.second;
                if (std::regex_match(lexeme, reservedReturn)){
                    type = TokenTypes::RETURN;
                }
                break;
            }
        }
        // if (match){
        //     throw std::runtime_error("Error en la línea " + std::to_string(lineNumber) + ": Token no válido '" + line[i] + "'");
        // }

        if (!lexeme.empty()){
            tokens.push_back(Token(type, lexeme, lineNumber));
            resultingTokens++;
        } 
    }
    tokens.push_back(Token(TokenTypes::EOF_TOKEN, "", lineNumber));
    return resultingTokens;
}


void Lexer::printTokens(){
    std::string typeName;
    for (auto token : this->tokens){
        typeName = tokenTypeToString(token.type);
        std::cout << "Type: " << typeName << ", Lexeme: " <<  token.lexeme << ", line: " << token.lineNumber << std::endl;
    }
}

// std::vector<Token> Lexer::getTokens(){
//     return this->tokens;
// }
