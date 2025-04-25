QT += core gui sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    check2fa.cpp \
    checkers.cpp \
    choosequiz.cpp \
    databasemanager.cpp \
    encryption.cpp \
    forgetpassword.cpp \
    homepage.cpp \
    homepagefunctions.cpp \
    main.cpp \
    mainwindow.cpp \
    pdf.cpp \
    question.cpp \
    quiz.cpp \
    quizexamen.cpp \
    sendemail.cpp \
    showpdfs.cpp \
    signin.cpp \
    signup.cpp \
    user.cpp

HEADERS += \
    check2fa.h \
    checkers.h \
    choosequiz.h \
    databasemanager.h \
    encryption.h \
    forgetpassword.h \
    homepage.h \
    homepagefunctions.h \
    mainwindow.h \
    pdf.h \
    question.h \
    quiz.h \
    quizexamen.h \
    sendemail.h \
    showpdfs.h \
    signin.h \
    signup.h \
    user.h

FORMS += \
    check2fa.ui \
    choosequiz.ui \
    forgetpassword.ui \
    homepage.ui \
    mainwindow.ui \
    quizexamen.ui \
    showpdfs.ui \
    signin.ui \
    signup.ui
RESOURCES += resources.qrc

INCLUDEPATH += C:/Users/PC/AppData/Local/Programs/Python/Python312/include
LIBS += -LC:/Users/PC/AppData/Local/Programs/Python/Python312/libs -lpython312

RESOURCES += \
    resources.qrc
