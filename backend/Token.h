#ifndef __TOKEN__
#define __TOKEN__
#include <string>

enum class TokenTypes{
    IDENTIFIER,
    PLUS_OPERATOR,
    MINUS_OPERATOR,
    DIVISION_OPERATOR,
    MULTIPLICATION_OPERATOR,
};

struct Token {
    TokenTypes type;
    std::string lexeme;
    Token * getToken();
    Token(std::string name, std::string value);
};

#endif