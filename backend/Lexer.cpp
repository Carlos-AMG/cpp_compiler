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
const std::regex Lexer::reservedWordsRegex("if|while|return|else|int|float");


const std::regex Lexer::binaryOperatorsRegex("[,!=%&*+-\\-><<==>>=^|]+");
const std::regex Lexer::unaryOperatorsRegex("[-!]|\\+\\+|--");







// Funcion encargada de analizar una cadena y usando las expresiones regulares debe guardar los tokens en una lista
// de tokens. Itera sobre la cadena y compara las expresiones para asi saber a que token pertenece
int Lexer::analyze(std::string line) {
    int resultingTokens = 0;
    std::string lexeme;
    TokenTypes type;
    std::string delimiters = "=-+";
    std::string whitespaces = " \n\t";
    int line_length = line.length();

    std::unordered_map<const std::regex*, TokenTypes> regexToTokenTypeMap = {
        {&identifierRegex, TokenTypes::IDENTIFIER},
        {&integerRegex, TokenTypes::INT_LITERAL},
        {&floatRegex, TokenTypes::FLOAT_LITERAL},
        {&reservedWordsRegex, TokenTypes::FLOAT_LITERAL}
    };

    // regexToTokenTypeMap[identifierRegex] = TokenTypes::IDENTIFIER;

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
                        // std::cout << line[++i] << std::endl;
                        // std::cout << (line[++i] == '+') << std::endl;
                        if (line[i+1] == '+'){
                            lexeme += line[++i];
                            type = TokenTypes::PLUS_PLUS_OP;
                        }
                        break;
                    case '-':
                        type = TokenTypes::SUBTRACTION_OP; 
                        if (line[i++] == '-'){
                            lexeme += line[i++];
                            type = TokenTypes::MINUS_MINUS_OP;
                        }              
                        break;
                    case '=':
                        type = TokenTypes::ASSIGNMENT_OP;
                        break; 
                    case '*':
                        type = TokenTypes::MULTIPLICATION_OP;
                        break; 
                    case '/':
                        type = TokenTypes::DIVISION_OP;
                        break; 
                }
                i++;
                tokens.push_back(Token(type, lexeme));
                continue;
        }
        // Continue building the lexeme until a delimiter is encountered
        // while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '=' && line[i] != '+') {
        // find wether it is an integer literal, float literal or identifier
        while (i < line_length && whitespaces.find(line[i]) == std::string::npos && delimiters.find(line[i]) == std::string::npos) {
            lexeme += line[i];
            // type = TokenTypes::IDENTIFIER;
            i++;
        }

        // Determine the token type based on the lexeme content using the map
        for (const auto& regexPair : regexToTokenTypeMap) {
            if (std::regex_match(lexeme, *(regexPair.first))) { // Compare lexeme to the pattern
                type = regexPair.second;
                break;
            }
        }

        tokens.push_back(Token(type, lexeme));
        resultingTokens++;
    }
    tokens.push_back(Token(TokenTypes::EOF_TOKEN, ""));
    return resultingTokens;
}


void Lexer::printTokens(){
    for (auto token : this->tokens){
        std::string typeName;
        switch (token.type)
        {
        case TokenTypes::IDENTIFIER:
            typeName = "IDENTIFIER";
            break;
        case TokenTypes::ADDITION_OP:
            typeName = "ADDITION_OP";
            break;
        case TokenTypes::ASSIGNMENT_OP:
            typeName = "ASSIGNMENT_OP";
            break;  
        case TokenTypes::SUBTRACTION_OP:
            typeName = "SUBTRACTION_OP";
            break; 
        case TokenTypes::MULTIPLICATION_OP:
            typeName = "MULTIPLICATION_OP";
            break;
        case TokenTypes::DIVISION_OP:
            typeName = "DIVISION_OP";
            break;
        case TokenTypes::PLUS_PLUS_OP:
            typeName = "PLUS_PLUS_OP";
            break;
        case TokenTypes:: MINUS_MINUS_OP:
            typeName = "MINUS_MINUS_OP";
            break;
        case TokenTypes::INT_LITERAL:
            typeName = "INT_LITERAL";
            break;
        case TokenTypes::FLOAT_LITERAL:
            typeName = "FLOAT_LITERAL";
            break;
        case TokenTypes::IF:
            typeName = "IF";
            break;
        case TokenTypes::ELSE:
            typeName = "ELSE";
            break;
        case TokenTypes::RETURN:
            typeName = "RETURN";
            break;
        case TokenTypes::EOF_TOKEN:
            typeName = "EOF";
            break;
        default:
            break;
        }
        std::cout << "Type: " << typeName << ", Lexeme: " <<  token.lexeme << std::endl;
    }
}

// std::vector<Token> Lexer::getTokens(){
//     return this->tokens;
// }
