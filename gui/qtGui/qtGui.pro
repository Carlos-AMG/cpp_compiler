QT += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Add your source files for the non-Qt code here
SOURCES += \
    ./main.cpp \
    ./mainwindow.cpp \
    ../../backend/Lexer.cpp \
    ../../backend/Parser.cpp \
    ../../backend/Token.cpp \ 
    ../../backend/utils/utils.cpp \ 
    ../../backend/SemanticParser.cpp \
    ../../backend/Symbol.cpp \
    ../../backend/SymbolTable.cpp 

HEADERS += \
    mainwindow.h \
    ../../backend/Lexer.h \
    ../../backend/Parser.h \
    ../../backend/Token.h \ 
    ../../backend/SemanticParser.h \
    ../../backend/Symbol.h \
    ../../backend/SymbolTable.h \
    ../../backend/utils/utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
