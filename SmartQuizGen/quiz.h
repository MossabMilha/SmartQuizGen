#ifndef QUIZ_H
#define QUIZ_H

#include "question.h"
#include <vector>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class Quiz {
public:
    Quiz();
    void addQuestion(const Question& question);
    std::vector<Question> getQuestions() const;
    bool saveToJson(const QString& filePath) const;
    bool loadFromJson(const QString& filePath);

private:
    std::vector<Question> questions;
};

#endif // QUIZ_H
