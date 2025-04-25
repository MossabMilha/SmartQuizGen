#ifndef FORGETPASSWORD_H
#define FORGETPASSWORD_H

#include <QWidget>
#include <random>

#include <QMessageBox>
#include "checkers.h"
#include "user.h"
#include "sendemail.h"
#include "check2fa.h"

namespace Ui {
class ForgetPassword;
}

class ForgetPassword : public QWidget
{
    Q_OBJECT

public:
    explicit ForgetPassword(QWidget *parent = nullptr);
    int GenerateCode();
    bool storeCodeToDB(int code,const std::string& email);
    ~ForgetPassword();

private:
    Ui::ForgetPassword *ui;
};

#endif // FORGETPASSWORD_H
