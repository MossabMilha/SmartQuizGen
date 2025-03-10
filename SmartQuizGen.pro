QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    question.cpp \
    quiz.cpp \
    quizexamen.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    homepage.h \
    mainwindow.h \
    question.h \
    quiz.h \
    quizexamen.h \
    signin.h \
    signup.h \
    user.h

FORMS += \
    homepage.ui \
    mainwindow.ui \
    quizexamen.ui \
    signin.ui \
    signup.ui

# Add Python include path and library
INCLUDEPATH += C:/Users/PC/AppData/Local/Programs/Python/Python312/include
LIBS += -LC:/Users/PC/AppData/Local/Programs/Python/Python312/libs -lpython312
