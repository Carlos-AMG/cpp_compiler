#include "Lexer.h"
#include <iostream>

enum test{
    GO,
    STOP
};

// Funcion que simplemente prueba la funcionalidad del Lexer (sin necesidad de bindings/gui)
int main(){
    Lexer lex1;
    std::string line = "x = a + b + c";
    // std::cout << "Write some text: ";
    // std::getline(std::cin, line);
    // // std::cout << line;
    lex1.analyze(line);
    std::cout << "Tokens: " << std::endl;
    lex1.printTokens();
    return 0;
}