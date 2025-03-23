#include "user.h"

// Constructor
User::User(const QString &fName, const QString &lName, const QString &uName, const QString &mail, const QString &pass)
    : firstName(fName), lastName(lName), username(uName), email(mail), password(pass) {}

// Getters
QString User::getFirstName() const { return firstName; }
QString User::getLastName() const { return lastName; }
QString User::getUsername() const { return username; }
QString User::getEmail() const { return email; }
QString User::getPassword() const { return password; }

// Setters
void User::setFirstName(const QString &fName) { firstName = fName; }
void User::setLastName(const QString &lName) { lastName = lName; }
void User::setUsername(const QString &uName) { username = uName; }
void User::setEmail(const QString &mail) { email = mail; }
void User::setPassword(const QString &pass) { password = pass; }
