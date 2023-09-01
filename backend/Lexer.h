#ifndef __LEXER__
#define __LEXER__

#include <vector>
#include "Token.h"

struct Lexer{
    std::vector<Token> tokens;
    int analyze(std::string line);
    void printTokens();
    std::vector<Token> getTokens();
};

#endif