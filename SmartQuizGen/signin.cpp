#include "signin.h"
#include "ui_signin.h"
#include "user.h"

#include "homepage.h"
#include <QMessageBox>

bool CheckSignIn(QString username, QString password, User &user) {
    if (User::isUsernameUsed(username)) {
        user = User::getUserByUsername(username);
        if (user.getPassword() == Encryption::encrypt(password)) {
            return true;
        }
    }
    return false;
}
SignIn::SignIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignIn)
{

    ui->setupUi(this);
    connect(ui->LoginButton, &QPushButton::clicked, this, [=]() {
        QString Username = ui->UsernameEntry->text().trimmed();
        QString Password = ui->PasswordEntry->text().trimmed();
        User user("", "", "", "", "", false);
        if(CheckSignIn(Username,Password,user)){
            HomePage* homePage = new HomePage(&user);
            homePage->show();
            this->hide();
        }else{

            QMessageBox::warning(this, "Input Error", "Username Or The Password  Are Incorrect");
            return;
        }
    });
}

SignIn::~SignIn()
{
    delete ui;
}
