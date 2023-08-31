#include "Lexer.h"
#include "utils/utils.h"
#include <iostream>

int Lexer::analize(std::string line){
    int i, j, k;
    int resultNumbers = 0;
    int lineLen = line.length();
    for (i=0; lineLen; i++){
        if (isspace(line[i])){
            continue;
        }
        if (isdigit(line[i])){
            for (j=i+1; j < lineLen; j++){
                if (!isdigit(line[j])){
                    break;
                }
            }
            this->tokens.insert(Token("INTEGER", line));
            resultNumbers++;
            i = j -1;
        } else if (isOperator(line[i])){
            this->tokens.insert(Token("OPERATOR", line));
        }else {
            // error
            // pending error class
            std::cerr << "Lexical Error: character: '"<< line[i] << "' is not valid in the source code";
        }
    }
}