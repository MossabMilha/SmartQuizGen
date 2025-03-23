#include "dbconnect.h"
#include "ui_dbconnect.h" // Include the generated UI header

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>



DBCConnect::DBCConnect(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DBCConnect)  // Initialize the ui pointer
{
    ui->setupUi(this);

    // Call the function to connect to the database
    connectToDatabase();
}

DBCConnect::~DBCConnect()
{
    delete ui;  // Clean up the ui pointer
}
