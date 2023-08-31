#include "Lexer.h"
#include "utils/utils.h"
#include <iostream>

int Lexer::analyze(std::string line){
    int i, j, k;
    int resultingTokens = 0;
    int lineLen = line.length();
    std::string tokenVal;
    std::cout << "Line: " << line << " line len: " << lineLen << std::endl;
    for (i=0; i < lineLen; i++){
        std::cout << i << std::endl;
        if (isspace(line[i])){
            std::cout << "white space" << std::endl;
            continue;
        }
        if (isdigit((line[i]))){
            std::string numericVal = "";
            numericVal += line[i];
            // int dot_count = 0; //for floats
            for (j=i+1; j < lineLen; j++){
                if (isspace(line[j])){
                    continue;
                }
                if (!isdigit(line[j]))
                    break;
                numericVal += line[j];
            }
            // std::cout << "klajsldkfja: " << j << std::endl;
            i = j - 1; // Move i to the last digit of the integer
            this->tokens.push_back(Token("INTEGER", numericVal));
            resultingTokens++;
        } else if (isOperator(line[i])){
            this->tokens.push_back(Token("OPERATOR", std::string(1, line[i])));
            resultingTokens++;
        }else {
            // error
            // pending error class
            std::cerr << "Lexical Error: character: '"<< line[i] << "' is not valid in the source code";
        }
    }
    return resultingTokens;
}

void Lexer::printTokens(){
    for (auto token : this->tokens){
        std::cout << "Token: " << token.name << ", Value: " << token.value << std::endl;
    }
}
