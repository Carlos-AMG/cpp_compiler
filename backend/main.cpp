#include "Lexer.h"
#include "Parser.h"
#include "utils/utils.h"
#include "SymbolTable.h"
#include <string>
#include <iostream>


int main(){
    Lexer lex1;
    SymbolTable table1;

    std::string text;
    try {
        text = readFile("./text.txt");
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Lexer lex;
    try {
        lex.analyze(text);
        lex.printTokens();
        Parser pars (lex.tokens);
        pars.parseProgram();
        std::cout << "valido" << std::endl;
    } catch (const std::exception& e){
        std::cerr << "Error" << e.what() << std::endl;
    }
    
    for (const auto& pair : table1.symbols) {
        std::cout << "Lexeme: " << pair.first << ", Type: " << tokenTypeToString(pair.second.type) << std::endl;
    }

    return 0;
}