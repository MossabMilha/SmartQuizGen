#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"
#include <vector>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSqlQuery>

class Quiz {
public:
    Quiz();
    Quiz(int id, int userId, int pdfId, const QString& createdAt);

    void addQuestion(const Question& question);
    std::vector<Question> getQuestions() const;
    bool loadFromJson(const QJsonObject& jsonObject);

    static std::vector<Quiz> getQuizsByUserId(int userId);


    // Getters
    int getId() const;
    int getUserId() const;
    int getPdfId() const;
    QString getCreatedAt() const;

private:
    int id;
    int userId;
    int pdfId;
    QString createdAt;
    std::vector<Question> questions;
};

#endif
