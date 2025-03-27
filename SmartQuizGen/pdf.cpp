#include "pdf.h"

pdf::pdf(int user_id, const std::string& filepath) : user_id(user_id) {
    filename = std::filesystem::path(filepath).filename().string();
    setData(filepath);
}


int pdf::getUserId() const {
    return user_id;
}


std::string pdf::getFilename() const {
    return filename;
}


std::string pdf::getData() const {
    return data;
}


void pdf::setUserId(int newUserId) {
    user_id = newUserId;
}

void pdf::setFilename(const std::string& newFilename) {
    filename = newFilename;
}


void pdf::setData(const std::string& path) {
    std::ifstream file(path, std::ios::binary);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << path << std::endl;
        return;
    }

    // Read the entire file
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    data.resize(fileSize); // Ensure string has enough space
    file.read(&data[0], fileSize);  // Read data into string

    file.close();
    std::cout << "File data read successfully and stored as BLOB" << std::endl;
}


bool pdf::savePdfToDb() {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO pdfs (user_id, filename, data) "
                  "VALUES (:user_id, :filename, :data)");

    query.bindValue(":user_id", user_id);
    query.bindValue(":filename", QString::fromStdString(filename));
    query.bindValue(":data", QByteArray::fromRawData(data.data(), data.size()));  // Converting std::string to QByteArray

    if (query.exec()) {
        id = query.lastInsertId().toInt();
        return true;
    } else {
        qDebug() << "Error saving PDF: " << query.lastError().text();
        return false;
    }
}
bool pdf::savePdfToDb(int &pdfId) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("INSERT INTO pdfs (user_id, filename, data) "
                  "VALUES (:user_id, :filename, :data)");

    query.bindValue(":user_id", user_id);
    query.bindValue(":filename", QString::fromStdString(filename));
    query.bindValue(":data", QByteArray::fromRawData(data.data(), data.size()));

    if (query.exec()) {

        pdfId = query.lastInsertId().toInt();
        return true;
    } else {
        return false;
    }
}
