#include "quiz.h"

void Quiz::addQuestion(const Question& question) {
    if (questions.size() < 10) {  // Ensure no more than 10 questions.
        questions.push_back(question);  // Add the question to the list.
    }
}

QJsonObject Quiz::toJson() const {
    QJsonObject json;

    // Create a QJsonArray to store all the questions.
    QJsonArray questionsArray;
    for (const auto& q : questions) {
        questionsArray.append(q.toJson());  // Convert each question to JSON and append.
    }

    json["quiz"] = questionsArray;  // Add the array of questions to the quiz JSON object.

    return json;  // Return the JSON representation of the quiz.
}
