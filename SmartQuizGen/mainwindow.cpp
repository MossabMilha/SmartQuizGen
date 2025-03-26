#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "signin.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->SignUpButton, &QPushButton::clicked, this, [=]() {
        SignUp *signupWindow = new SignUp(this);
        signupWindow->show();
        this->hide();
    });
    connect(ui->SignInButton, &QPushButton::clicked, this, [=]() {
        SignIn *signinWindow = new SignIn(this);
        signinWindow->show();
        this->hide();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
