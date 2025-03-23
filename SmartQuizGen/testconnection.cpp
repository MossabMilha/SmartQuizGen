#include "testconnection.h"
#include "ui_testconnection.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

testconnection::testconnection(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::testconnection)
{
    ui->setupUi(this);

    // Connect to SQLite database
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:/Users/PC/Desktop/sqllitedbtest/test.db");

    if (!db.open()) {
        qDebug() << "Database connection failed:" << db.lastError().text();
    } else {
        qDebug() << "Database connected successfully!";

        // Example query: Create a table if it doesn't exist
        // Get and display table names
        QStringList tables = db.tables();
        if (tables.isEmpty()) {
            qDebug() << "No tables found in the database.";
        } else {
            qDebug() << "Tables in the database:";
            for (const QString &table : tables) {
                qDebug() << table;
            }
        }
    }
}

testconnection::~testconnection()
{
    delete ui;
    QSqlDatabase::database().close(); // Close the database connection
}
