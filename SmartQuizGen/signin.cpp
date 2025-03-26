#include "signin.h"
#include "ui_signin.h"
#include "user.h"

#include "homepage.h"
#include <QMessageBox>


SignIn::SignIn(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignIn)
{

    ui->setupUi(this);
    User* user = new User("Mossab","Milha","MMILHA","mossabmilha.m@gmail.com","mossab");
    connect(ui->LoginButton, &QPushButton::clicked, this, [=]() {
        QString Username = ui->UsernameEntry->text().trimmed();
        QString Password = ui->PasswordEntry->text().trimmed();
        if(Username == user->getUsername() && Password == user->getPassword() ){
            HomePage* homePage = new HomePage(user);
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
