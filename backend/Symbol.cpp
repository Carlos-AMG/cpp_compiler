#include "Symbol.h"

Symbol::Symbol(const std::string& lexeme, TokenTypes type): lexeme(lexeme), type(type) {}
Symbol::Symbol():lexeme{"null"}, type{TokenTypes::EOF_TOKEN}{}