#ifndef PDF_H
#define PDF_H

#include "databasemanager.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <string>
#include <filesystem>
#include <QFile>
#include <QFileDialog>

class pdf {
private:
    int id;
    int user_id;
    std::string filename;
    std::string data;
    std::string uploaded_at;

public:
    // Constructor
    pdf(int user_id, const std::string& filepath);

    // Getters
    int getUserId() const;
    std::string getFilename() const;
    std::string getData() const;

    // Setters
    void setUserId(int newUserId);
    void setFilename(const std::string& newFilename);
    void setData(const std::string& path);

    bool savePdfToDb();
    bool savePdfToDb(int& pdfId);
};

#endif // PDF_H
