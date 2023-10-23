#include "utils.h"
#include <fstream>
#include <sstream>

bool isOperator(char character){
    return (character == '+' || character == '-' || character == '*' || character == '/');
}

std::string readFile(const std::string& filePath) {
    std::ifstream inFile(filePath);
    if (!inFile) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    std::stringstream buffer;
    buffer << inFile.rdbuf();
    return buffer.str();
}