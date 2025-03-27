#ifndef HOMEPAGE_H
#define HOMEPAGE_H


#include "ui_HomePage.h"
#include "homepagefunctions.h"
#include "quizexamen.h"

#include "user.h"
#include "pdf.h"
#include "quiz.h"
#include "question.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <QProcess>
#include <QFile>
#include <QDialog>

namespace Ui {
class HomePage;
}

class User;

class HomePage : public QDialog {
    Q_OBJECT

private:
    bool generateAllowed = false;
    QString uploadedFilePath;  // Declare uploadedFilePath as a member variable

public:
    explicit HomePage(User* user, QWidget *parent = nullptr);
    ~HomePage();

private:
    Ui::HomePage *ui;
    User* currentUser;
};

#endif // HOMEPAGE_H
