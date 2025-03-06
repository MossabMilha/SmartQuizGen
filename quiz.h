#ifndef QUIZ_H
#define QUIZ_H

#include <vector>
#include "Question.h"
#include <QJsonObject>
#include <QJsonArray>

class Quiz {
public:
    std::vector<Question> questions;  // List of questions in the quiz.

    // Method to add a question to the quiz. Limits the number of questions to 10.
    void addQuestion(const Question& question);

    // Method to convert the entire quiz into a JSON object.
    QJsonObject toJson() const;
};

#endif // QUIZ_H
