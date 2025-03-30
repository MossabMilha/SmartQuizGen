#include "pdf.h"

pdf::pdf(int user_id, const std::string& filepath) : user_id(user_id) {
    filename = std::filesystem::path(filepath).filename().string();
    setData(filepath);
}
pdf::pdf(int id, int user_id, const std::string& filename, const std::string& uploaded_at)
    : id(id), user_id(user_id), filename(filename), uploaded_at(uploaded_at) {
    data = "Not Available";
}

int pdf::getId() const{
    return id;
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
void pdf::setDataFromBinary(const std::vector<char>& binaryData) {
    // Store the binary data directly
    data.assign(binaryData.begin(), binaryData.end());
    std::cout << "Binary data stored successfully as BLOB" << std::endl;
}

bool pdf::pdfHaveQuiz(int pdfId) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("SELECT COUNT(*) FROM quizzes WHERE pdf_id = :pdfId");
    query.bindValue(":pdfId", pdfId);

    if (!query.exec()) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        return query.value(0).toInt() > 0;
    }

    return false;
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
    query.bindValue(":data", QByteArray::fromRawData(data.data(), data.size()));

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

std::vector<pdf> pdf::getPdfsOfUser(int userId) {
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return std::vector<pdf>();
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, filename, uploaded_at FROM pdfs WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    std::vector<pdf> userPdfs;

    if (!query.exec()) {
        qDebug() << "Error fetching PDFs for user:" << query.lastError().text();
        return userPdfs;
    }

    while (query.next()) {
        int id = query.value("id").toInt();
        std::string filename = query.value("filename").toString().toStdString();
        std::string uploaded_at = query.value("uploaded_at").toString().toStdString();

        // Use the constructor where data is always set to "Not Available"
        pdf pdfEntry(id, userId, filename, uploaded_at);  // Use the updated constructor

        // No need to manually set 'id' and 'uploaded_at' as it's already set by the constructor
        userPdfs.push_back(pdfEntry);
    }

    if (userPdfs.empty()) {
        qDebug() << "No PDFs found for user with ID:" << userId;
    }

    return userPdfs;
}


