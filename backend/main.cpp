#include "Lexer.h"
#include "Parser.h"
#include <iostream>

enum test{
    GO,
    STOP
};

// Funcion que simplemente prueba la funcionalidad del Lexer (sin necesidad de bindings/gui)
int main(){
    Lexer lex1;
    Parser pars1;
    std::string line;
    // std::string line = "x = a + b + c";
    std::cout << "Write some text: ";
    std::getline(std::cin, line);
    lex1.analyze(line);
    std::cout << "Tokens: " << std::endl;
    lex1.printTokens();
    pars1.parse(lex1.tokens);

    return 0;
}