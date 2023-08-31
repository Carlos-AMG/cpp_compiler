#ifndef __TOKEN__
#define __TOKEN__
#include <string>

struct Token {
    std::string name;
    std::string value;
    Token * getToken();
    Token(std::string name, std::string value);
};

#endif