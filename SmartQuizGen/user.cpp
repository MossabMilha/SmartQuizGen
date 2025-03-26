#include "user.h"

// Constructor
User::User(const QString &fName, const QString &lName, const QString &uName, const QString &mail, const QString &pass, bool CanBeSave)
    : firstName(fName), lastName(lName), username(uName), email(mail), CanBeSave(CanBeSave) {
    setPassword(pass);  // Encrypt the password during construction
}
// Getters
QString User::getFirstName() const { return firstName; }
QString User::getLastName() const { return lastName; }
QString User::getUsername() const { return username; }
QString User::getEmail() const { return email; }
QString User::getPassword() const { return Encryption::decrypt(password);}
QString User::getSaveState() const { return CanBeSave ? "True" : "False"; }

// Setters
void User::setFirstName(const QString &fName) { firstName = fName; }
void User::setLastName(const QString &lName) { lastName = lName; }
void User::setUsername(const QString &uName) { username = uName; }
void User::setEmail(const QString &mail) { email = mail; }
void User::setPassword(const QString &pass) { password = Encryption::encrypt(pass); }


// Save state setters
void User::SaveStateTrue() { CanBeSave = true; }
void User::SaveStateFalse() { CanBeSave = false; }


bool User::isUsernameUsed(const QString& username) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE username = :username");
    query.bindValue(":username", username);
    if (!query.exec()) {
        return false;
    }
    return query.next() && query.value(0).toInt() > 0;
}

bool User::isEmailUsed(const QString& email) {
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        return false;
    }
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE email = :email");
    query.bindValue(":email", email);
    if (!query.exec()) {
        return false;
    }
    return query.next() && query.value(0).toInt() > 0;
}

bool User::saveUserToDb() {

    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }


    QSqlQuery query;


    query.prepare("INSERT INTO users (FirstName, LastName,Username,Password,email)"
                  "VALUES (:firstName, :lastName, :username, :password, :email)");

    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":canBeSaved", CanBeSave);

    if (!query.exec()) {
        return false;
    }


    return true;
}
