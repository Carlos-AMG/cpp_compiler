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
        std::string delimiters = "=-+";
        
        // Skip whitespace characters
       while (i < line.length() && (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')) {
            i++;
        }
        
        // Operators
        if (i < line.length() && (line[i] == '=' || line[i] == '+')) {
            lexeme += line[i];
            i++;
        }

        // Continue building the lexeme until a delimiter is encountered
        // while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && line[i] != '=' && line[i] != '+') {
        while (i < line.length() && line[i] != ' ' && line[i] != '\t' && line[i] != '\n' && delimiters.find(line[i]) == std::string::npos) {
            lexeme += line[i];
            i++;
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