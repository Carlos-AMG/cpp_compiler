#include "Lexer.h"
#include <iostream>

enum test{
    GO,
    STOP
};

// Funcion que simplemente prueba la funcionalidad del Lexer (sin necesidad de bindings/gui)
int main(){
    // Lexer lex1;
    // std::string line;
    // std::cout << "Write some text: ";
    // std::getline(std::cin, line);
    // // std::cout << line;
    // lex1.analyze(line);
    // std::cout << "Tokens: " << std::endl;
    // lex1.printTokens();
    test test1 = GO;
    std::string line = "int x = 20 + 2";
    std::string lexeme;
    std::vector<std::string> lexemes = {};
    for (int i = 0; i < line.length(); i++){
        lexeme = "";
        if (line[i] == ' ' or line[i] == '\n')
            continue;
        
        if (line[i] == '='){
            lexeme += line[i];
            i++;
            lexemes.push_back(lexeme);
            continue;
        }else if (line[i] == '+'){
            lexeme += line[i];
            i++;
            lexemes.push_back(lexeme);
            continue;
        }
        for (int j = i; j < line.length(); j++){
            if (line[j] == ' ' or line[j] == '=' or line[j] == '+'){
                i = j;
                break;
            }
            i++;
            lexeme += line[j];
        }
        // std::cout << lexeme << std::endl;
        lexemes.push_back(lexeme);
    }

    for (auto lexeme: lexemes){
        std::cout << lexeme << std::endl;
    }
    // for (auto ch: str1){
    //     std::cout << ch << std::endl;
    // }

    return 0;
}