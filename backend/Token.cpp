#include "Token.h"

Token::Token(std::string name, std::string value): name(name), value(value){}
Token * Token::getToken(){
    return this;
} 