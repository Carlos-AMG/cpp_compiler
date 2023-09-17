#include "Lexer.h"
#include "utils/utils.h"
#include <iostream>
#include <regex>

// int Lexer::analyze(std::string line){
//     int i, j, k;
//     int resultingTokens = 0;
//     int lineLen = line.length();
//     std::string tokenVal;
//     for (i=0; i < lineLen; i++){
//         if (isspace(line[i])){
//             continue;
//         }
//         if (isdigit((line[i]))){
//             std::string numericVal = "";
//             numericVal += line[i];
//             // int dot_count = 0; //for floats
//             for (j=i+1; j < lineLen; j++){
//                 if (isspace(line[j])){
//                     continue;
//                 }
//                 if (!isdigit(line[j]))
//                     break;
//                 numericVal += line[j];
//             }
//             i = j - 1; // Move i to the last digit of the integer
//             this->tokens.push_back(Token("INTEGER", numericVal));
//             resultingTokens++;
//         } else if (isOperator(line[i])){
//             this->tokens.push_back(Token("OPERATOR", std::string(1, line[i])));
//             resultingTokens++;
//         }else {
//             // error
//             // pending error class
//             std::cerr << "Lexical Error: character: '"<< line[i] << "' is not valid in the source code";
//         }
//     }
//     return resultingTokens;
// }


// Define and initialize the static const regex members
const std::regex Lexer::identifierRegex("[a-zA-Z][a-zA-Z0-9]*");
const std::regex Lexer::integerRegex("[0-9]+");
const std::regex Lexer::realRegex("[0-9]+\\.[0-9]+");
const std::regex Lexer::stringRegex("\"[^\"]*\"");
const std::regex Lexer::additionOperatorRegex("[\\+\\-]");
const std::regex Lexer::multiplicationOperatorRegex("[\\*/]");
const std::regex Lexer::assignmentOperatorRegex("=");
const std::regex Lexer::relationalOperatorRegex("[<>]=?|!=|==");
const std::regex Lexer::logicalAndOperatorRegex("&&");
const std::regex Lexer::logicalOrOperatorRegex("\\|\\|");
const std::regex Lexer::logicalNotOperatorRegex("!");
const std::regex Lexer::leftParenthesisRegex("\\(");
const std::regex Lexer::rightParenthesisRegex("\\)");
const std::regex Lexer::leftBraceRegex("\\{");
const std::regex Lexer::rightBraceRegex("\\}");
const std::regex Lexer::semicolonRegex(";");
const std::regex Lexer::reservedWordsRegex("if|while|return|else|int|float");

// int Lexer::analyze(std::string line) {
//     int i = 0;
//     int resultingTokens = 0;
//     int lineLen = line.length();

//     while (i < lineLen) {
//         // Skip consecutive whitespace
//         while (i < lineLen && isspace(line[i])) {
//             i++;
//         }

//         if (i >= lineLen) {
//             // Reached the end of the line, exit the loop
//             break;
//         }

//         // Find the end of the current token
//         int lexemeEnd = i;

//         // Check if the current character is an operator
//         if (std::regex_match(std::string(1, line[i]), additionOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), multiplicationOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), assignmentOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), relationalOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), logicalAndOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), logicalOrOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), logicalNotOperatorRegex) ||
//             std::regex_match(std::string(1, line[i]), leftParenthesisRegex) ||
//             std::regex_match(std::string(1, line[i]), rightParenthesisRegex) ||
//             std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
//             std::regex_match(std::string(1, line[i]), rightBraceRegex) ||
//             std::regex_match(std::string(1, line[i]), semicolonRegex)) {
            
//             // If it's an operator, add it as a separate token
//             std::string currentOperator(1, line[i]);
//             this->tokens.push_back(Token("OPERATOR", currentOperator));
//             resultingTokens++;
//             i++; // Move to the next character
//         }
//         else {
//             // Find the end of the current token (lexemeEnd)
//             while (lexemeEnd < lineLen && !isspace(line[lexemeEnd]) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), additionOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), multiplicationOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), assignmentOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), relationalOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), logicalAndOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), logicalOrOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), logicalNotOperatorRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), leftParenthesisRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), rightParenthesisRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), leftBraceRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), rightBraceRegex) &&
//                 !std::regex_match(std::string(1, line[lexemeEnd]), semicolonRegex)) {
//                 lexemeEnd++;
//             }

//             // Extract the current token as a substring
//             std::string currentLexeme = line.substr(i, lexemeEnd - i);
//             std::cout << "lexeme: " << currentLexeme << std::endl;

//             if (std::regex_match(currentLexeme, reservedWordsRegex)) {
//                 if (std::regex_search(currentLexeme, reservedWordsRegex)) {
//                     this->tokens.push_back(Token("RESERVED", currentLexeme));
//                     resultingTokens++;
//                 } else {
//                     // Handle the case where there's no match (error)
//                     std::cerr << "Lexical Error: Unexpected characters starting with '" << line[i] << "'" << std::endl;
//                     // i++; // Skip the invalid character
//                 }
//             }
//             else if (std::regex_match(currentLexeme, integerRegex)) {
//                 this->tokens.push_back(Token("INTEGER", currentLexeme));
//                 resultingTokens++;
//             }
//             else if (std::regex_match(currentLexeme, realRegex)) {
//                 this->tokens.push_back(Token("FLOAT", currentLexeme));
//                 resultingTokens++;
//             }
//             else if (std::regex_match(currentLexeme, identifierRegex)) {
//                 this->tokens.push_back(Token("IDENTIFIER", currentLexeme));
//                 resultingTokens++;
//             }
//             else {
//                 // error
//                 // pending error class
//                 std::cerr << "Lexical Error: character: '" << line[i] << "' is not valid in the source code" << std::endl;
//                 // i++; // Skip the invalid character
//             }

//             i = lexemeEnd;
//         }
//     }

//     return resultingTokens;
// }


int Lexer::analyze(std::string line) {
    int i = 0;
    int resultingTokens = 0;
    int lineLen = line.length();

    while (i < lineLen) {
        // Skip consecutive whitespace
        while (i < lineLen && isspace(line[i])) {
            i++;
        }

        if (i >= lineLen) {
            // Reached the end of the line, exit the loop
            break;
        }

        // Find the end of the current token
        int lexemeEnd = i;

        // Check if the current character is an operator or string delimiter
        if (std::regex_match(std::string(1, line[i]), additionOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), multiplicationOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), assignmentOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), relationalOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), logicalAndOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), logicalOrOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), logicalNotOperatorRegex) ||
            std::regex_match(std::string(1, line[i]), leftParenthesisRegex) ||
            std::regex_match(std::string(1, line[i]), rightParenthesisRegex) ||
            std::regex_match(std::string(1, line[i]), leftBraceRegex) ||
            std::regex_match(std::string(1, line[i]), rightBraceRegex) ||
            std::regex_match(std::string(1, line[i]), semicolonRegex)) {

            // If it's an operator, add it as a separate token
            std::string currentOperator(1, line[i]);
            this->tokens.push_back(Token("OPERATOR", currentOperator));
            resultingTokens++;
            i++; // Move to the next character
        }
        else if (line[i] == '"') {
            // Handle string literals
            int stringStart = i;
            i++; // Move past the opening double quote

            while (i < lineLen && line[i] != '"') {
                i++; // Move to the end of the string
            }

            if (i < lineLen) {
                // Found the closing double quote
                i++; // Move past the closing double quote
                std::string currentString = line.substr(stringStart, i - stringStart);
                this->tokens.push_back(Token("STRING", currentString));
                resultingTokens++;
            } else {
                // Missing closing double quote
                std::cerr << "Lexical Error: Unterminated string literal starting at position " << stringStart << std::endl;
                break;
            }
        }
        else {
            // Find the end of the current token (lexemeEnd)
            while (lexemeEnd < lineLen && !isspace(line[lexemeEnd]) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), additionOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), multiplicationOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), assignmentOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), relationalOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), logicalAndOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), logicalOrOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), logicalNotOperatorRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), leftParenthesisRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), rightParenthesisRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), leftBraceRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), rightBraceRegex) &&
                !std::regex_match(std::string(1, line[lexemeEnd]), semicolonRegex)) {
                lexemeEnd++;
            }

            // Extract the current token as a substring
            std::string currentLexeme = line.substr(i, lexemeEnd - i);
            std::cout << "lexeme: " << currentLexeme << std::endl;

            if (std::regex_match(currentLexeme, reservedWordsRegex)) {
                if (std::regex_search(currentLexeme, reservedWordsRegex)) {
                    this->tokens.push_back(Token("RESERVED", currentLexeme));
                    resultingTokens++;
                } else {
                    // Handle the case where there's no match (error)
                    std::cerr << "Lexical Error: Unexpected characters starting with '" << line[i] << "'" << std::endl;
                    // i++; // Skip the invalid character
                }
            }
            else if (std::regex_match(currentLexeme, integerRegex)) {
                this->tokens.push_back(Token("INTEGER", currentLexeme));
                resultingTokens++;
            }
            else if (std::regex_match(currentLexeme, realRegex)) {
                this->tokens.push_back(Token("FLOAT", currentLexeme));
                resultingTokens++;
            }
            else if (std::regex_match(currentLexeme, identifierRegex)) {
                this->tokens.push_back(Token("IDENTIFIER", currentLexeme));
                resultingTokens++;
            }
            else {
                // error
                // pending error class
                std::cerr << "Lexical Error: character: '" << line[i] << "' is not valid in the source code" << std::endl;
                // i++; // Skip the invalid character
            }

            i = lexemeEnd;
        }
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
