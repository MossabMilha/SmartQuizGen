QT += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    checkers.cpp \
    choosequiz.cpp \
    databasemanager.cpp \
    encryption.cpp \
    homepage.cpp \
    homepagefunctions.cpp \
    main.cpp \
    mainwindow.cpp \
    pdf.cpp \
    question.cpp \
    quiz.cpp \
    quizexamen.cpp \
    showpdfs.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    checkers.h \
    choosequiz.h \
    databasemanager.h \
    encryption.h \
    homepage.h \
    homepagefunctions.h \
    mainwindow.h \
    pdf.h \
    question.h \
    quiz.h \
    quizexamen.h \
    showpdfs.h \
    signin.h \
    signup.h \
    user.h

FORMS += \
    choosequiz.ui \
    homepage.ui \
    mainwindow.ui \
    quizexamen.ui \
    showpdfs.ui \
    signin.ui \
    signup.ui


INCLUDEPATH += C:/Users/PC/AppData/Local/Programs/Python/Python312/include
LIBS += -LC:/Users/PC/AppData/Local/Programs/Python/Python312/libs -lpython312
