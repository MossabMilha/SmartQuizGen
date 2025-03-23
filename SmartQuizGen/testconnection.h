#ifndef TESTCONNECTION_H
#define TESTCONNECTION_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class testconnection;
}

class testconnection : public QDialog
{
    Q_OBJECT

public:
    explicit testconnection(QWidget *parent = nullptr);
    ~testconnection();

private:
    Ui::testconnection *ui;
    QSqlDatabase db;  // Database object to manage the connection
};

#endif // TESTCONNECTION_H
