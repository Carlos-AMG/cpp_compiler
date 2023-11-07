#ifndef __SYMBOL__
#define __SYMBOL__
#include <string>
#include "Token.h"


struct Symbol {
    std::string lexeme;
    TokenTypes type;

    Symbol(const std::string& lexeme, TokenTypes type);
    Symbol();
};

#endif