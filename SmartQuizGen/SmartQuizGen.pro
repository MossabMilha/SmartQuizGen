QT += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    checkers.cpp \
    databasemanager.cpp \
    encryption.cpp \
    homepage.cpp \
    main.cpp \
    mainwindow.cpp \
    pdf.cpp \
    question.cpp \
    quiz.cpp \
    quizexamen.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    checkers.h \
    databasemanager.h \
    encryption.h \
    homepage.h \
    mainwindow.h \
    pdf.h \
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


INCLUDEPATH += C:/Users/PC/AppData/Local/Programs/Python/Python312/include
LIBS += -LC:/Users/PC/AppData/Local/Programs/Python/Python312/libs -lpython312
