#include "question.h"

Question::Question(const QString& q, const std::vector<QString>& opts, const QString& correct)
    : question(q), options(opts), correct_answer(correct) {}

QJsonObject Question::toJson() const {
    QJsonObject obj;

    obj["question"] = question;  // Add the question text to the JSON object.

    // Create a QJsonArray to store the options (A, B, C, D).
    QJsonArray optionsArray;
    for (const auto& option : options) {
        optionsArray.append(option);  // Append each option to the array.
    }
    obj["options"] = optionsArray;  // Add options to the JSON object.

    obj["correct_answer"] = correct_answer;  // Add the correct answer to the JSON object.

    return obj;  // Return the JSON representation of the question.
}
