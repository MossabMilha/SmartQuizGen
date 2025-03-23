#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

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
    bool validateInputs(QString firstName, QString lastName, QString username,
                        QString email, QString password, QString confirmPassword,
                        QString &ErrorMessage);

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
