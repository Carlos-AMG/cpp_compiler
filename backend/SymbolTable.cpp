#include "SymbolTable.h"


void SymbolTable::insert(const std::string& identifier, TokenTypes type) {
    symbols[identifier] = Symbol(identifier, type);
}

Symbol SymbolTable::lookup(const std::string& identifier) {
    if (symbols.find(identifier) == symbols.end()) {
        throw std::runtime_error("Identifier not found in symbol table");
    }
    return symbols[identifier];
}