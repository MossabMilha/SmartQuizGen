#ifndef USER_H
#define USER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include "encryption.h"

class User {
private:
    QString firstName;
    QString lastName;
    QString username;
    QString email;
    QString password;
    bool CanBeSave;

public:
    // Constructor
    User(const QString &fName, const QString &lName, const QString &uName, const QString &mail, const QString &pass,bool CanBeSave=false);

    // Getters
    QString getFirstName() const;
    QString getLastName() const;
    QString getUsername() const;
    QString getEmail() const;
    QString getPassword() const;
    QString getSaveState() const;

    // Setters
    void setFirstName(const QString &fName);
    void setLastName(const QString &lName);
    void setUsername(const QString &uName);
    void setEmail(const QString &mail);
    void setPassword(const QString &pass);

    // Save state setters
    void SaveStateTrue();
    void SaveStateFalse();

    // Static methods for checking database
    static bool isUsernameUsed(const QString& username);
    static bool isEmailUsed(const QString& email);


    bool saveUserToDb();
};

#endif // USER_H
