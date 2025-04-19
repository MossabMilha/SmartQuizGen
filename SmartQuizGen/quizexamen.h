#ifndef QUIZEXAMEN_H
#define QUIZEXAMEN_H

#include <QDialog>
#include "quiz.h"
#include "user.h"// Assuming you have a Quiz class with a method getQuestions()

namespace Ui {
class QuizExamen;
}

class QuizExamen : public QDialog
{
    Q_OBJECT

public:
    explicit QuizExamen(User* user ,Quiz *quiz, QWidget *parent = nullptr);

    void saveCurrentAnswer();
    void displayQuestion(const Question& question);
    void updateNavigationButtons(int totalQuestions);

    ~QuizExamen();


private:
    Ui::QuizExamen *ui;
    Quiz *quiz;
    void displayQuestions();
    int currentQuestionIndex;
    int *userAnswers;
    User* currentUser;

};

#endif
