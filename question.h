#ifndef QUESTION_H
#define QUESTION_H

#include <QString>
#include <vector>

class Question {
public:
    Question(const QString& text, const std::vector<QString>& options, const QString& correctAnswer);

    QString getText() const;
    std::vector<QString> getOptions() const;
    QString getCorrectAnswer() const;

private:
    QString text;
    std::vector<QString> options;
    QString correctAnswer;
};

#endif // QUESTION_H
