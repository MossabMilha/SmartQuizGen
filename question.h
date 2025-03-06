#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <vector>

class Question {
public:
    QString question;
    std::vector<QString> options;
    QString correct_answer;


    Question(const QString& q, const std::vector<QString>& opts, const QString& correct);


    QJsonObject toJson() const;
};

#endif
