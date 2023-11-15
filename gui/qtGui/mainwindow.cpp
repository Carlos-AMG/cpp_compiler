#include "mainwindow.h"
#include "../../backend/Lexer.h"
#include "../../backend/Parser.h"
#include "../../backend/utils/utils.h"
#include "../../backend/Token.h"
#include "../../SymbolTable.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <iostream>

bool error = false; 
Qstring semanticString = "";


Token validateTree(ASTNode* node, SymbolTable& table) {
    if (node == nullptr) {
        return Token(TokenTypes::NULLT, "null");
    }

    if (auto binOpNode = dynamic_cast<BinaryOpNode*>(node)) {
        auto lhs = validateTree(binOpNode->left, table);
        auto rhs = validateTree(binOpNode->right, table);

        Symbol temp;
        if (lhs.type == TokenTypes::IDENTIFIER){
            temp = table.lookup(lhs.lexeme);
            lhs.type = temp.type;         
        }
        if (rhs.type == TokenTypes::IDENTIFIER){
            temp = table.lookup(rhs.lexeme);
            rhs.type = temp.type;  
        }

        if (binOpNode->op_tok.type == TokenTypes::DIVISION_OP && rhs.lexeme == "0") {
            // std::cout << "Error: División entre cero, en la línea: " << binOpNode->op_tok.lineNumber << std::endl;
            semanticString += ("Error: División entre cero, en la línea: " + std::to_string(binOpNode->op_tok.lineNumber) + "\n");
            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("División entre cero");
        }

        if (lhs.type != rhs.type) {
            // std::cout << "Error: Tipos incompatibles en la línea: " << binOpNode->op_tok.lineNumber << std::endl;
            semanticString += ("Error: Tipos incompatibles en la línea: " + std::to_string(binOpNode->op_tok.lineNumber)) + "\n";

            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("Tipos incompatibles");
        }

        return lhs;  // Podrías devolver rhs si ambos deben ser iguales
    } else if (auto unaryNode = dynamic_cast<UnaryOpNode*>(node)) {
        validateTree(unaryNode->operand, table);
    } else if (auto numNode = dynamic_cast<NumberNode*>(node)) {
        return numNode->tok;
    } else if (auto assignmentNode = dynamic_cast<AssignmentNode*>(node)) { // x = 1
        auto lhs = assignmentNode->identifier;
        auto rhs = validateTree(assignmentNode->expression, table);
        table.insert(lhs.lexeme, rhs.type);
        validateTree(assignmentNode->expression, table);
    } else if (auto strNode = dynamic_cast<StringNode*>(node)){
        return strNode->string;
    } else if (auto idNode = dynamic_cast<IdentifierNode*>(node)) {
        auto identifier = table.lookup(idNode->identifier.lexeme);
        if (identifier.type == TokenTypes::NULLT) {
            // std::cout << "Error: Variable no declarada: " << idNode->identifier.lexeme << " en la línea: " << idNode->identifier.lineNumber << std::endl;
            semanticString += ("Error: Variable no declarada: " + std::to_string(idNode->identifier.lexeme)  + " en la línea: " + std::to_string(idNode->identifier.lineNumber));
            
            // Puedes lanzar una excepción aquí si lo prefieres
            // throw std::runtime_error("Variable no declarada");
        }
        return(idNode->identifier);
    } else if (auto returnNode = dynamic_cast<ReturnStatementNode*>(node)) {
        validateTree(returnNode->expression, table);
    } else if (auto ifNode = dynamic_cast<IfStatementNode*>(node)) {
        validateTree(ifNode->condition, table);
        validateTree(ifNode->if_body, table);
        if (ifNode->else_body != nullptr) {
            validateTree(ifNode->else_body, table);
        }
    } else if (auto programNode = dynamic_cast<ProgramNode*>(node)) {
        for (ASTNode* statement : programNode->statements) {
            validateTree(statement, table);
        }
    }

    return Token();  // Otra opción es devolver un token nulo por defecto
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    Lexer lex1;
    SymbolTable table1;
    QString lexicalString = "";
    QString parserString = "";

    std::string text;
    try {
        text = readFile("text.txt");
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Lexer lex;

    try {
        lex.analyze(text);
        std::string tokType;
        for (Token token: lex.tokens){
            std::cout << "token: " << token.lexeme << std::endl;
            std::string line = "";
            tokType = tokenTypeToString(token.type);
            line += "Token: [" + tokType + "], Lexeme: " + token.lexeme + "\n";
            lexicalString += QString::fromStdString(line);
        }
    } catch(const std::exception& e){
        lexicalString += QString::fromStdString("Lexical error: " + std::string(e.what()));
    }


    try {
        Parser pars(lex.tokens);
        pars.parseProgram();
        parserString = QString::fromStdString("Sentencias validas");
    } catch (const std::exception& e){
        parserString = QString::fromStdString("Parsing error: " + std::string(e.what()));
    }

    validateTree(tree, table1)
    // try {
    //     validateTree(tree, table1);

    // }

   QString textToDisplay = QString::fromStdString(text);

    ui->textBrowser->setPlainText(lexicalString);
    ui->textBrowser_2->setPlainText(semanticString);

}


void MainWindow::on_pushButton_2_clicked()
{
    // Get the text from the QTextEdit widget
    QString textToSave = ui->textEdit->toPlainText();

    if (textToSave.isEmpty()) {
        QMessageBox::warning(this, "Warning", "Text is empty. Nothing to save.");
        return;
    }

    // Specify the file path where you want to save the text
    QString filePath = "text.txt";

    // Create a QFile object to write to the file
    QFile file(filePath);

    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        // Create a QTextStream to write the text to the file
        QTextStream out(&file);
        out << textToSave;
        file.close();
        QMessageBox::information(this, "Success", "Text saved to 'output.txt'.");
    } else {
        QMessageBox::critical(this, "Error", "Failed to open the file for writing.");
    }
}

