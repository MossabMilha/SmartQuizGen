#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>


#include "signin.h"
#include "mainwindow.h"

#include "user.h"
#include "checkers.h"
#include <string>

#include <QRegularExpression>
#include <QMessageBox>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    bool validateInputs(User newuser, QString confirmPassword, QMap<QString, QString>& ErrorMessages);

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
