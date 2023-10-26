#ifndef __LEXER__
#define __LEXER__

#include <vector>
#include "Token.h"
#include <regex>

// declaracion de clase Lexer la cual contiene una lista de tokens, la cual la funcion de analizar llenara con los respectivos tokens
// adicionalmente contiene las expresiones regulares para los diferentes tokens


struct Lexer{
    std::vector<Token> tokens;
    int analyze(std::string line);
    void printTokens();
    // std::vector<Token> getTokens();


    static const std::regex identifierRegex;
    static const std::regex integerRegex;
    static const std::regex floatRegex;
    static const std::regex stringRegex;
    static const std::regex additionOperatorRegex;
    static const std::regex multiplicationOperatorRegex;
    static const std::regex assignmentOperatorRegex;
    static const std::regex relationalOperatorRegex;
    static const std::regex logicalAndOperatorRegex;
    static const std::regex logicalOrOperatorRegex;
    static const std::regex logicalNotOperatorRegex;
    static const std::regex leftParenthesisRegex;
    static const std::regex rightParenthesisRegex;
    static const std::regex leftBraceRegex;
    static const std::regex rightBraceRegex;
    static const std::regex semicolonRegex;
    static const std::regex reservedWordsRegex;
    static const std::regex ifRegex;
    static const std::regex elseRegex;
    static const std::regex whileRegex;
    static const std::regex reservedIntRegex;
    static const std::regex reservedFloatRegex;
    static const std::regex reservedReturn;


    // Binary operators defined by this: https://learn.microsoft.com/en-us/cpp/cpp/binary-operators?view=msvc-170
    static const std::regex binaryOperatorsRegex;
    static const std::regex unaryOperatorsRegex;
};

#endif