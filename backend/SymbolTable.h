#ifndef __SYMBOL_TABLE__
#define __SYMBOL_TABLE__

#include "Token.h"
#include "Symbol.h"
#include <unordered_map>
#include <string>
#include <iostream>


struct SymbolTable {
    std::unordered_map<std::string, Symbol> symbols;
    void insert(const std::string& identifier, TokenTypes type);
    Symbol lookup(const std::string& identifier);
};

#endif