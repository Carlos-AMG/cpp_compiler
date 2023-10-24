#include "mainwindow.h"
#include "../../backend/Lexer.h"
#include "../../backend/Parser.h"
#include "../../backend/utils/utils.h"
#include "../../backend/Token.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

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
    std::string text;
    try {
        text = readFile("text.txt");
    } catch (const std::exception & e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    Lexer lex1 = Lexer();
    lex1.analyze(text);
    std::string tokType;
    QString textToDisplay = "";


    for (Token token: lex1.tokens){
        std::string line = "";
        tokType = tokenTypeToString(token.type);
        line += "Token: " + tokType + ", Lexeme: " + token.lexeme + "\n";
        textToDisplay += QString::fromStdString(line);

    }

//    QString textToDisplay = QString::fromStdString(text);

    ui->textBrowser->setPlainText(textToDisplay);

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

