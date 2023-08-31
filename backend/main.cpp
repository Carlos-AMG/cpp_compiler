#include "Lexer.h"
#include <iostream>

int main(){
    Lexer lex1;
    std::string line;
    std::cout << "Write some text: ";
    std::getline(std::cin, line);
    // std::cout << line;
    lex1.analyze(line);
    // lex1.printTokens();

    return 0;
}