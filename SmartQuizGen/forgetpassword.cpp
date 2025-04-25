#include "forgetpassword.h"
#include "ui_forgetpassword.h"



int ForgetPassword::GenerateCode(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(100000, 999999);

    return dist(gen);
}
bool ForgetPassword::storeCodeToDB(int code,const std::string& email){
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }


    QSqlQuery query;

    query.prepare("REPLACE INTO password_resets (email, code, expiration) "
                  "VALUES (:email, :code, datetime('now', '+10 minutes'))");

    query.bindValue(":email", QString::fromStdString(email));
    query.bindValue(":code", QString::number(code));



    if (!query.exec()) {
        return false;
    }


    return true;
}
ForgetPassword::ForgetPassword(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ForgetPassword)
{
    ui->setupUi(this);
    connect(ui->ComfirmEmail, &QPushButton::clicked, this, [=]() {
        QString email = ui->EmailEntry->text().trimmed();

        if (!Checkers::EmailIsValid(email.toStdString())) {
            QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
            return;
        }

        if (!User::isEmailUsed(email)) {
            QMessageBox::warning(this, "Email Not Found", "This email doesn't have an associated account.");
            return;
        }

        int code = GenerateCode();

        QString accessToken = "";// Token Here

        SendEmail mailer;
        if (mailer.sendEmailWithCode(email, code, accessToken)) {
            QMessageBox::information(this, "Email Sent", "A reset code has been sent to your email address.");
            Check2FA* Check2FAPage = new Check2FA(code,email);
            Check2FAPage->show();
            this->hide();

        } else {
            QMessageBox::critical(this, "Email Failed", "Failed to send the reset code. Please try again.");
        }
    });
}

ForgetPassword::~ForgetPassword()
{
    delete ui;
}
