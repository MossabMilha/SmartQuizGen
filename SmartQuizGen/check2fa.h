#ifndef CHECK2FA_H
#define CHECK2FA_H

#include <QWidget>
#include <QMessageBox>
#include "user.h"
#include "checkers.h"
#include "mainwindow.h"

namespace Ui {
class Check2FA;
}

class Check2FA : public QWidget
{
    Q_OBJECT

public:
    explicit Check2FA(int code,QString email, QWidget *parent = nullptr);
    ~Check2FA();

private:
    Ui::Check2FA *ui;
};

#endif // CHECK2FA_H
