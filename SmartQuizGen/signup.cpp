#include "signup.h"
#include "ui_signup.h"

bool SignUp::validateInputs(User newuser, QString confirmPassword, QMap<QString, QString>& ErrorMessages){
    bool isPass = true;
    ErrorMessages["EmptyFields"] = "false";
    QString firstName = newuser.getFirstName();
    QString lastName = newuser.getLastName();
    QString username = newuser.getUsername();
    QString email = newuser.getEmail();
    QString password = newuser.getPassword();


    if (firstName.isEmpty() || lastName.isEmpty() || username.isEmpty() || email.isEmpty() || password.isEmpty()) {
        ErrorMessages["EmptyFields"] = "⚠️ All fields must be filled!\n";
        return false;
    }

    if (!Checkers::NameIsValid(firstName.toStdString())) {
        ErrorMessages["Name"] = "❌ First And Last Name Should only contain letters, hyphens, or apostrophes.\n";
        isPass = false;
    }else{
        ErrorMessages["Name"] = "false";
    }

    if (username.length() < 5) {
        ErrorMessages["username"]= "🔹 Username must be at least 5 characters long.\n";
        isPass = false;
    }else{
        if(User::isUsernameUsed(username)){
            ErrorMessages["username"] = "🔹This Username Already Used.\n";
            isPass = false;
        }else{
            ErrorMessages["username"] = "false";
        }
    }

    if (!Checkers::EmailIsValid(email.toStdString())) {
        ErrorMessages["email"] = "📧 Please enter a valid email (e.g., example@domain.com).\n";
        isPass = false;
    }else{
        if(User::isEmailUsed(email)){
            ErrorMessages["email"] = "📧 This Email Already In used.\n";
            isPass = false;
        }else{
            ErrorMessages["email"] = "false";
        }
    }

    if (!Checkers::PasswordIsValid(newuser, password.toStdString())) {
        ErrorMessages["password"] = "🔒 Password must be at least 8 characters, contain one uppercase letter and one number.\n";
        isPass = false;
    }else{
        ErrorMessages["password"] = "false";
        if(password != confirmPassword){
            ErrorMessages["confirmPassword"] = "🔄 Passwords do not match!\n";
            isPass = false;
        }else{
            ErrorMessages["confirmPassword"] = "false";
        }
    }

    return isPass;
}

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{

    ui->setupUi(this);
    connect(ui->SignInButton, &QPushButton::clicked, this, [=]() {
        SignIn *signinWindow = new SignIn(this);
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
        bool agree = ui->Agreements->isChecked();


        User newUser(firstName, lastName, username, email, password);
        QMap<QString, QString> ErrorMessages;
        if (!validateInputs(newUser, confirmPassword, ErrorMessages)) {
            QString allErrors;
            for (const auto &error : ErrorMessages) {
                if (error != "false") {
                    allErrors += error;
                }
            }
            QMessageBox::warning(this, "Input Error", allErrors);
            return;
        }else if(!agree){
            QMessageBox::warning(this, "Input Error", "You Should Agree To Our Terms");
            return;
        }


        newUser.SaveStateTrue();
        if(newUser.saveUserToDb()){
            MainWindow *mainWindow = new MainWindow(this);
            QMessageBox::information(this, "Success", "🎉 Sign-up Successful!");
            mainWindow->show();
            this->hide();
        }else{
            QMessageBox::warning(this, "Input Error", "Ther's Problem In SignUp");
        }
    });

    connect(ui->BackHomePage, &QPushButton::clicked, this, [=]() {

        MainWindow* MainWindowPage = new MainWindow();
        MainWindowPage->show();
        this->hide();

    });

    bool isVisible = true;
    connect(ui->SeeHidePassword, &QPushButton::clicked, this, [=]() mutable {
        isVisible = !isVisible;
        ui->PasswordEntry->setEchoMode(isVisible ? QLineEdit::Normal : QLineEdit::Password);
        QIcon icon(isVisible ? ":/images/images/visible.png" : ":/images/images/hide.png");
        ui->SeeHidePassword->setIcon(icon);
    });

    bool isConfirmVisible = true;
    connect(ui->SeeHideConfirmPassword, &QPushButton::clicked, this, [=]() mutable {
        isConfirmVisible = !isConfirmVisible;
        ui->ConfirmPasswordEntry->setEchoMode(isConfirmVisible ? QLineEdit::Normal : QLineEdit::Password);
        QIcon icon(isConfirmVisible ? ":/images/images/visible.png" : ":/images/images/hide.png");
        ui->SeeHideConfirmPassword->setIcon(icon);
    });





}

SignUp::~SignUp()
{
    delete ui;
}
