QT += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    checkers.cpp \
    databasemanager.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    question.cpp \
    quiz.cpp \
    quizexamen.cpp \
    signin.cpp \
    signup.cpp \
    testconnection.cpp \
    user.cpp

HEADERS += \
    checkers.h \
    databasemanager.h \
    homepage.h \
    mainwindow.h \
    question.h \
    quiz.h \
    quizexamen.h \
    signin.h \
    signup.h \
    testconnection.h \
    user.h

FORMS += \
    homepage.ui \
    mainwindow.ui \
    quizexamen.ui \
    signin.ui \
    signup.ui \
    testconnection.ui

# Add Python include path and library
INCLUDEPATH += C:/Users/PC/AppData/Local/Programs/Python/Python312/include
LIBS += -LC:/Users/PC/AppData/Local/Programs/Python/Python312/libs -lpython312
