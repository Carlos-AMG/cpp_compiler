#include "mainwindow.h"

#include "../../backend/Lexer.h"
#include "../../backend/Parser.h"
#include "../../backend/utils/utils.h"
#include <string>
#include <iostream>
#include <QCoreApplication>
#include <QDir>

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();



    return a.exec();
}
