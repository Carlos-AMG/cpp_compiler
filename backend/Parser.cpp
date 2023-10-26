// #include "Parser.h"
#include "Parser.h"
#include "utils/utils.h"
#include <iostream>



Parser::Parser(const std::vector<Token> & inputTokens): tokens{inputTokens}, curr_idx{0}{}

Token Parser::currentToken(){
    if (curr_idx < tokens.size()){
        return tokens[curr_idx];
    }
    return {TokenTypes::EOF_TOKEN, ""};
}

void Parser::advance(){
    curr_idx++;
}

ASTNode* Parser::parseProgram() {
    std::vector<ASTNode*> programStatements;


    while (currentToken().type != TokenTypes::EOF_TOKEN) {
        programStatements.push_back(parseStatement());
    }

    // En lugar de devolver un vector, crea un nodo ProgramNode que contenga las declaraciones.
    return new ProgramNode(programStatements);
}

ASTNode* Parser::parseStatement() {
    if (currentToken().type == TokenTypes::IF) {
        return parseIfStatement();
    } else if (currentToken().type == TokenTypes::RETURN) {
        return parseReturnStatement();
    } else if (currentToken().type == TokenTypes::ASSIGNMENT_OP) {
        return parseAssignment();
    }

    // Si no coincide con ninguno de los tipos de declaración anteriores, asumir que es una expresión
    return parseExpression();
}

ASTNode* Parser::parseIfStatement() {
    advance();  // Avanzar al token RESERVED_IF

    if (currentToken().type == TokenTypes::LEFT_PAREN) {
        advance();  // Avanzar al paréntesis izquierdo
        ASTNode* condition = parseExpression();        
        if (currentToken().type == TokenTypes::RIGHT_PAREN) {
            advance();  // Avanzar al paréntesis derecho

            ASTNode* if_body = parseBlock();  // Implementa parseBlock para analizar el bloque de código

            ASTNode* else_body = nullptr;
            if (currentToken().type == TokenTypes::ELSE) {
                advance();  // Avanzar al token RESERVED_ELSE
                else_body = parseBlock();  // Implementa parseBlock para analizar el bloque else
            }

            return new IfStatementNode(condition, if_body, else_body);
        } else {
            throw std::runtime_error("Expected a closing parenthesis on line number: " + std::to_string(currentToken().lineNumber) );
        }
    } else {
        throw std::runtime_error("Expected an opening parenthesis after 'if'");
    }
}

ASTNode* Parser::parseBlock() {
    if (currentToken().type == TokenTypes::LEFT_BRACKET) {
        advance();  // Avanzar al token LEFT_BRACKET

        std::vector<ASTNode*> statements;

        while (currentToken().type != TokenTypes::RIGHT_BRACKET) {
            ASTNode* statement = parseStatement();
            statements.push_back(statement);
        }

        advance();  // Avanzar al token RIGHT_BRACKET

        // Crea un nodo ProgramNode para representar el bloque de código
        return new ProgramNode(statements);
    } else {
        throw std::runtime_error("Expected an opening curly brace for the block");
    }
}


ASTNode* Parser::parseAssignment() {
    Token identifierToken = currentToken();
    // advance();  // Avanzar al identificador
    if (currentToken().type == TokenTypes::ASSIGNMENT_OP) {
        advance();  // Avanzar al operador de asignación
        ASTNode* expression = parseExpression();
        return new AssignmentNode(identifierToken, expression);
    } else {
        throw std::runtime_error("Expected an assignment operator");
    }
}


ASTNode* Parser::parseExpression() {
    return parseLogicalOr();
}

ASTNode* Parser::parseLogicalOr() {
    ASTNode* left = parseLogicalAnd();

    while (currentToken().type == TokenTypes::OR_OP) {
        Token opToken = currentToken();
        advance();  // Avanzamos al siguiente token, que debe ser un 'logical_and'.
        ASTNode* right = parseLogicalAnd();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}

ASTNode* Parser::parseLogicalAnd() {
    ASTNode* left = parseEquality();

    while (currentToken().type == TokenTypes::AND_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* right = parseEquality();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}

ASTNode* Parser::parseEquality() {
    ASTNode* left = parseRelational();

    while (currentToken().type == TokenTypes::EQUALITY_OP || currentToken().type == TokenTypes::INEQUALITY_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* right = parseRelational();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}

ASTNode* Parser::parseRelational() {
    ASTNode* left = parseAdditive();

    while (currentToken().type == TokenTypes::MORE_THAN_OP || currentToken().type == TokenTypes::LESS_THAN_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* right = parseAdditive();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}

ASTNode* Parser::parseAdditive() {
    ASTNode* left = parseMultiplicative();

    while (currentToken().type == TokenTypes::ADDITION_OP || currentToken().type == TokenTypes::SUBTRACTION_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* right = parseMultiplicative();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}

ASTNode* Parser::parseMultiplicative() {
    ASTNode* left = parseUnary();

    while (currentToken().type == TokenTypes::MULTIPLICATION_OP || currentToken().type == TokenTypes::DIVISION_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* right = parseUnary();
        left = new BinaryOpNode(left, opToken, right);
    }

    return left;
}
ASTNode* Parser::parseUnary() {
    if (currentToken().type == TokenTypes::ADDITION_OP || currentToken().type == TokenTypes::SUBTRACTION_OP) {
        Token opToken = currentToken();
        advance();
        ASTNode* operand = parseUnary();
        return new UnaryOpNode(opToken, operand);
    } else {
        return parsePrimary();
    }
}

ASTNode* Parser::parsePrimary() {
    Token currTok = currentToken();
    if (currentToken().type == TokenTypes::IDENTIFIER) {
        advance();
        return new IdentifierNode(currTok);
        // return new IdentifierNode(currentToken());
    } else if (currentToken().type == TokenTypes::INT_LITERAL || currentToken().type == TokenTypes::FLOAT_LITERAL) {
        advance();
        return new NumberNode(currTok);
        // return new NumberNode(currentToken());
    } else if (currentToken().type == TokenTypes::STRING_LITERAL){
        advance();
        return new StringNode(currTok);
    }
    else if (currentToken().type == TokenTypes::LEFT_PAREN) {
        advance();  // Avanza el token LEFT_PAREN
        ASTNode* expression = parseExpression();
        if (currentToken().type == TokenTypes::RIGHT_PAREN) {
            advance();  // Avanza el token RIGHT_PAREN
            return expression;
        } else {
            throw std::runtime_error("Expected a closing parenthesis on line: " + std::to_string(currTok.lineNumber));
        }
    } else {
        throw std::runtime_error("Unexpected token: " + tokenTypeToString(currTok.type) + "  in primary expression");
    }
}

ASTNode* Parser::parseReturnStatement() {
    std::cout << "reyes no tiene manjaro" << std::endl;
    advance();  // Avanzar al token RESERVED_RETURN
    ASTNode* expression = parseExpression();
    if (currentToken().type == TokenTypes::SEMICOLON) {
        advance();  // Avanzar al punto y coma
        return new ReturnStatementNode(expression);
    } else {
        throw std::runtime_error("Expected a semicolon at the end of the return statement");
    }
}








