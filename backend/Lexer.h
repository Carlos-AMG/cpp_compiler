#ifndef __LEXER__
#define __LEXER__

#include <vector>
#include "Token.h"

struct Lexer{
    std::vector<Token> tokens;
    int analize(std::string line);
};

#endif