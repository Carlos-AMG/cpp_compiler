#include "Token.h"

// inicializador del token, guarda el tipo y el lexema (value en este caso)
// Token::Token(std::string type, std::string lexeme): name(name), lexeme(lexeme){}
Token::Token(TokenTypes type, std::string lexeme): type(type), lexeme(lexeme){}
// Token * Token::getToken(){
//     return this;
// } 