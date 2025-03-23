#include "signup.h"
#include "ui_signup.h"
#include "signin.h"
#include "mainwindow.h"

#include "user.h"

#include <QRegularExpression>
#include <QMessageBox>

bool SignUp::validateInputs(QString firstName, QString lastName, QString username, QString email, QString password, QString confirmPassword, QString &ErrorMessage) {
    bool isPass = true;

    QRegularExpression nameRegex("^[A-Za-z'-]+$");
    QRegularExpression emailRegex("^[\\w-]+(\\.[\\w-]+)*@([\\w-]+\\.)+[a-zA-Z]{2,7}$");
    QRegularExpression passwordRegex("^(?=.*[A-Z])(?=.*\\d)[A-Za-z\\d]{8,}$"); // At least 8 characters, 1 uppercase, 1 digit

    if (firstName.isEmpty() || lastName.isEmpty() || username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        ErrorMessage += "⚠️ All fields must be filled!\n";
        isPass = false;
    }

    if (!nameRegex.match(firstName).hasMatch() || !nameRegex.match(lastName).hasMatch()) {
        ErrorMessage += "❌ First or Last name should only contain letters, hyphens, or apostrophes.\n";
        isPass = false;
    }

    if (username.length() < 5) {
        ErrorMessage += "🔹 Username must be at least 5 characters long.\n";
        isPass = false;
    }

    if (!emailRegex.match(email).hasMatch()) {
        ErrorMessage += "📧 Please enter a valid email (e.g., example@domain.com).\n";
        isPass = false;
    }

    if (!passwordRegex.match(password).hasMatch()) {
        ErrorMessage += "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.\n";
        isPass = false;
    }

    if (password != confirmPassword) {
        ErrorMessage += "🔄 Passwords do not match!\n";
        isPass = false;
    }

    // Log errors for debugging
    if (!isPass) {
        qDebug() << "Validation failed: " << ErrorMessage;
    }

    return isPass;
}

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
    connect(ui->SignInButton, &QPushButton::clicked, this, [=]() {
        SignIn *signinWindow = new SignIn(this); // Create the signup window
        signinWindow->show();  // Show it
        this->hide();
    });
    connect(ui->FinishSignupButton, &QPushButton::clicked, this, [=]() {
        QString firstName = ui->FirstNameEntry->text().trimmed();
        QString lastName = ui->LastNameEntry->text().trimmed();
        QString username = ui->UsernameEntry->text().trimmed();
        QString email = ui->EmailEntry->text().trimmed();
        QString password = ui->PasswordEntry->text();
        QString confirmPassword = ui->ConfirmPasswordEntry->text();
        QString ErrorMessage = "";

        if (!validateInputs(firstName, lastName, username, email, password, confirmPassword, ErrorMessage)) {
            QMessageBox::warning(this, "Input Error", ErrorMessage);
            return;
        }

        // ✅ If validation passes, create a User object
        User newUser(firstName, lastName, username, email, password);

        // Here, you can save the user data (e.g., in a database)

        MainWindow *mainWindow = new MainWindow(this);
        mainWindow->show();
        QMessageBox::information(this, "Success", "🎉 Sign-up Successful!");
        this->hide();
    });

}

SignUp::~SignUp()
{
    delete ui;
}
