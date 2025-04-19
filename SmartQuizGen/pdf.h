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
#include <set>

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
    pdf(int id,int user_id, const std::string& filename, const std::string& uploaded_at);

    // Getters
    int getId() const;
    int getUserId() const;
    std::string getFilename() const;
    std::string getData() const;
    std::string getuploaded_at() const;
    static std::vector<pdf> getPdfsOfUser(int userId );
    static bool pdfHaveQuiz(int pdfId);
    static std::string getFilenameByPdfID(int pdfId);

    // Setters
    void setUserId(int newUserId);
    void setFilename(const std::string& newFilename);
    void setData(const std::string& path);
    void setDataFromBinary(const std::vector<char>& binaryData);

    bool savePdfToDb();
    bool savePdfToDb(int& pdfId);
};

#endif // PDF_H
