#include "Token.h"

// inicializador del token, guarda el tipo y el lexema (value en este caso)
// Token::Token(std::string type, std::string lexeme): name(name), lexeme(lexeme){}
Token::Token(TokenTypes type, std::string lexeme): type(type), lexeme(lexeme){}
Token::Token(TokenTypes type, std::string lexeme, size_t lineNumber): type(type), lexeme(lexeme), lineNumber{lineNumber}{}
Token::Token(): type{TokenTypes::IDENTIFIER}, lexeme{""}{}
// Token * Token::getToken(){
//     return this;
// } 

Token::Token(const Token& other){
    this->type = other.type;
    this->lexeme = other.lexeme;
    this->lineNumber = other.lineNumber;
}
