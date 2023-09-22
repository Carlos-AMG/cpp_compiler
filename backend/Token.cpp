#include "Token.h"

// inicializador del token, guarda el tipo y el lexema (value en este caso)
Token::Token(std::string name, std::string value): name(name), value(value){}
Token * Token::getToken(){
    return this;
} 