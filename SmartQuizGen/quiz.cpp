#include "quiz.h"
#include <QFile>
#include <QJsonDocument>
#include <QTextStream>
#include <QDebug>

Quiz::Quiz() {}

void Quiz::addQuestion(const Question& question) {
    questions.push_back(question);
}

std::vector<Question> Quiz::getQuestions() const {
    return questions;
}

bool Quiz::saveToJson(const QString& filePath) const {
    QJsonArray quizArray;

    for (const auto& question : questions) {
        QJsonObject questionObj;
        questionObj["question"] = question.getText();

        QJsonArray optionsArray;
        for (const auto& option : question.getOptions()) {
            optionsArray.append(option);
        }
        questionObj["options"] = optionsArray;
        questionObj["correct_answer"] = question.getCorrectAnswer();

        quizArray.append(questionObj);
    }

    QJsonObject root;
    root["quiz"] = quizArray;

    QJsonDocument doc(root);
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) {
        qWarning() << "Failed to open file for writing:" << filePath;
        return false;
    }

    QTextStream out(&file);
    out << doc.toJson(QJsonDocument::Indented);
    file.close();

    return true;
}

bool Quiz::loadFromJson(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Failed to open file for reading:" << filePath;
        return false;
    }

    QByteArray jsonData = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(jsonData);
    if (doc.isNull()) {
        qWarning() << "Failed to parse JSON.";
        return false;
    }

    questions.clear();
    QJsonObject root = doc.object();
    QJsonArray quizArray = root["quiz"].toArray();

    for (const QJsonValue& value : quizArray) {
        QJsonObject questionObj = value.toObject();
        QString questionText = questionObj["question"].toString();
        QString correctAnswer = questionObj["correct_answer"].toString();

        std::vector<QString> options;
        for (const QJsonValue& optionValue : questionObj["options"].toArray()) {
            options.push_back(optionValue.toString());
        }

        questions.emplace_back(questionText, options, correctAnswer);
    }

    return true;
}
