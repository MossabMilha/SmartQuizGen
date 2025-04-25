#include "check2fa.h"
#include "ui_check2fa.h"

Check2FA::Check2FA(int code, QString email, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Check2FA)
{
    ui->setupUi(this);
    ui->NewPassword->setVisible(false);
    ui->NewPasswordText->setVisible(false);
    ui->ConfirmPassword->setVisible(false);
    ui->ConfirmPasswordText->setVisible(false);
    ui->changePassword->setVisible(false);
    connect(ui->Check2FAButton, &QPushButton::clicked, [this, code, email]() {
        int enteredCode = ui->Code2FA->text().toInt();

        if (enteredCode == code) {

            ui->Code2FAText->setVisible(false);
            ui->Code2FA->setVisible(false);
            ui->Check2FAButton->setVisible(false);
            ui->NewPassword->setVisible(true);
            ui->NewPasswordText->setVisible(true);
            ui->ConfirmPassword->setVisible(true);
            ui->ConfirmPasswordText->setVisible(true);
            ui->changePassword->setVisible(true);

        } else {
            ui->Code2FA->clear();
        }
    });
    connect(ui->changePassword, &QPushButton::clicked, [this, email]() {
        User user = User::getUserByEmail(email);
        QString password = ui->NewPassword->text();
        QString confirmPassword = ui->ConfirmPassword->text();

        if (!Checkers::PasswordIsValid(user, password.toStdString())) {
            QMessageBox::warning(this, "Invalid Password", "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.\n");

        }else{

            if(password != confirmPassword){
                QMessageBox::warning(this, "Invalid Password", "🔄 Passwords do not match!\n");
            }else{
                if (user.ChangePassword(email, password)) {
                    QMessageBox::information(this, "Success", "✅ Password changed successfully!");
                    MainWindow* MainWindowPage = new MainWindow();
                    MainWindowPage->show();
                    this->hide();
                } else {
                    QMessageBox::critical(this, "Error", "❌ Failed to update password. Please try again.");
                }
            }
        }
    });

}

Check2FA::~Check2FA()
{
    delete ui;
}
