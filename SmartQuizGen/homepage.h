#ifndef HOMEPAGE_H
#define HOMEPAGE_H

#include <QDialog>

namespace Ui {
class HomePage;
}

class User;

class HomePage : public QDialog {
    Q_OBJECT

private:
    bool generateAllowed = false;
    QString uploadedFilePath;  // Declare uploadedFilePath as a member variable

public:
    explicit HomePage(User* user, QWidget *parent = nullptr);
    ~HomePage();

private:
    Ui::HomePage *ui;
    User* currentUser;
};

#endif // HOMEPAGE_H
