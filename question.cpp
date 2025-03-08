#include "question.h"

Question::Question(const QString& text, const std::vector<QString>& options, const QString& correctAnswer)
    : text(text), options(options), correctAnswer(correctAnswer) {}

QString Question::getText() const {
    return text;
}

std::vector<QString> Question::getOptions() const {
    return options;
}

QString Question::getCorrectAnswer() const {
    return correctAnswer;
}
