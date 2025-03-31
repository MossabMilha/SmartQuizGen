#include "quiz.h"
#include "qsqldatabase.h"
#include "qsqlerror.h"
#include <QFile>
#include <QJsonDocument>
#include <QTextStream>
#include <QDebug>

Quiz::Quiz() : id(-1), userId(-1), pdfId(-1), createdAt("") {}

Quiz::Quiz(int id, int userId, int pdfId, const QString& createdAt)
    : id(id), userId(userId), pdfId(pdfId), createdAt(createdAt) {}

void Quiz::addQuestion(const Question& question) {
    questions.push_back(question);
}

std::vector<Question> Quiz::getQuestions() const {
    return questions;
}

// Load quiz from JSON data (this will be used for both file and database loading)
bool Quiz::loadFromJson(const QJsonObject& jsonObject) {
    // Clear previous questions
    questions.clear();

    // Parse metadata from JSON
    if (jsonObject.contains("id")) {
        id = jsonObject["id"].toInt();
    }
    if (jsonObject.contains("user_id")) {
        userId = jsonObject["user_id"].toInt();
    }
    if (jsonObject.contains("pdf_id")) {
        pdfId = jsonObject["pdf_id"].toInt();
    }
    if (jsonObject.contains("created_at")) {
        createdAt = jsonObject["created_at"].toString();
    }

    // Parse questions array from JSON
    if (jsonObject.contains("quiz")) {
        QJsonArray quizArray = jsonObject["quiz"].toArray();
        for (const QJsonValue& value : quizArray) {
            QJsonObject questionObj = value.toObject();
            QString questionText = questionObj["question"].toString();
            QString correctAnswer = questionObj["correct_answer"].toString();

            std::vector<QString> options;
            QJsonArray optionsArray = questionObj["options"].toArray();
            for (const QJsonValue& option : optionsArray) {
                options.push_back(option.toString());
            }

            // Create Question object and add to the questions vector
            Question question(questionText, options, correctAnswer);
            addQuestion(question);
        }
    }

    return true;
}


// Fetch quizzes by user ID from the database
std::vector<Quiz> Quiz::getQuizsByUserId(int userId) {
    std::vector<Quiz> quizzes;
    QSqlDatabase db = QSqlDatabase::database();

    if (!db.isOpen()) {
        qWarning() << "Database is not open!";
        return quizzes;
    }

    QSqlQuery query;
    query.prepare("SELECT id, user_id, pdf_id, created_at, data FROM quizzes WHERE user_id = :userId");
    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qWarning() << "Failed to retrieve quizzes:" << query.lastError().text();
        return quizzes;
    }

    while (query.next()) {
        int id = query.value(0).toInt();
        int userId = query.value(1).toInt();
        int pdfId = query.value(2).toInt();
        QString createdAt = query.value(3).toString();
        QByteArray jsonData = query.value(4).toByteArray();

        // Convert QByteArray to QJsonDocument and then to QJsonObject
        QJsonDocument doc = QJsonDocument::fromJson(jsonData);
        if (doc.isNull()) {
            qWarning() << "Failed to parse JSON for quiz ID:" << id;
            continue; // Skip this quiz if parsing fails
        }
        QJsonObject jsonObject = doc.object();

        // Create the Quiz object
        Quiz quiz(id, userId, pdfId, createdAt);

        // Load questions from JSON
        if (quiz.loadFromJson(jsonObject)) {
            quizzes.push_back(quiz);
        } else {
            qWarning() << "Failed to load questions for quiz ID:" << id;
        }
    }

    return quizzes;
}

// Getters
int Quiz::getId() const { return id; }
int Quiz::getUserId() const { return userId; }
int Quiz::getPdfId() const { return pdfId; }
QString Quiz::getCreatedAt() const { return createdAt; }
