#ifndef UTILS_H
#define UTILS_H
#include <string>
#include <vector>
#include "../Token.h"
#include "Parser.h"

bool isOperator(char character);
std::string readFile(const std::string & filePath);
std::string tokenTypeToString(TokenTypes type);
std::vector<std::string> readLinesFromFile(const std::string& filePath);
void PrintAST(ASTNode* node, int indent);

#endif 
