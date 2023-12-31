#ifndef __TOKEN__
#define __TOKEN__
#include <string>

enum class TokenTypes{
    NULLT,
    IDENTIFIER,
    INT_LITERAL,
    FLOAT_LITERAL,
    STRING_LITERAL,
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACKET,
    RIGHT_BRACKET,
    COMMA,
    SEMICOLON,
    NOT_OP,
    ADDITION_OP,
    SUBTRACTION_OP,
    MULTIPLICATION_OP,
    DIVISION_OP,
    EQUALITY_OP,
    INEQUALITY_OP,
    LESS_THAN_OP,
    LESS_EQUAL_OP,
    MORE_THAN_OP,
    MORE_EQUAL_OP,
    ASSIGNMENT_OP,
    PLUS_PLUS_OP,
    MINUS_MINUS_OP,
    AND_OP,
    OR_OP,
    IF,
    ELSE,
    WHILE,
    RETURN,
    FOR,
    INTEGER,
    FLOAT,
    CHAR,
    VOID, 
    STRING,
    EOF_TOKEN
};

struct Token {
    long lineNumber;
    TokenTypes type;
    std::string lexeme;
    // Token * getToken();
    Token();
    Token(TokenTypes type, std::string lexeme, size_t lineNumber);
    Token(TokenTypes type, std::string lexeme);
    Token(const Token& other);
};

#endif