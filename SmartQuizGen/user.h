    #ifndef USER_H
    #define USER_H

    #include <QString>

    class User {
    private:
        QString firstName;
        QString lastName;
        QString username;
        QString email;
        QString password;

    public:
        // Constructor
        User(const QString &fName, const QString &lName, const QString &uName, const QString &mail, const QString &pass);

        // Getters
        QString getFirstName() const;
        QString getLastName() const;
        QString getUsername() const;
        QString getEmail() const;
        QString getPassword() const;

        // Setters
        void setFirstName(const QString &fName);
        void setLastName(const QString &lName);
        void setUsername(const QString &uName);
        void setEmail(const QString &mail);
        void setPassword(const QString &pass);
    };

    #endif // USER_H
