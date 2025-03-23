#include "testdb.h"
#include "ui_testdb.h"
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

void connectToDatabase() {
    qDebug() << "Available Drivers: " << QSqlDatabase::drivers();

    // Create an SQLite database connection
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    // Set the correct database file path
    QString dbPath = "C:/Users/PC/Desktop/sqllitedbtest/test.db";  // Adjust path if needed
    db.setDatabaseName(dbPath); // Use the path to the SQLite database file

    // Open the connection
    if (!db.open()) {
        qDebug() << "Error: " << db.lastError().text();
    } else {
        qDebug() << "Database connected!";
    }
}

TestDb::TestDb(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TestDb)
{
    ui->setupUi(this);
    connectToDatabase();
    displayTableData();
}

void TestDb::displayTableData()
{
    // Create a query to get the list of tables
    QSqlQuery query("SELECT name FROM sqlite_master WHERE type='table';");

    if (query.lastError().isValid()) {
        qDebug() << "Query Error: " << query.lastError().text();
        return;
    }

    // Print all the table names to the debug output
    qDebug() << "Tables in database:";
    while (query.next()) {
        QString tableName = query.value(0).toString();  // Get the table name
        qDebug() << tableName;  // Print the table name
    }
}

TestDb::~TestDb()
{
    delete ui;
}
