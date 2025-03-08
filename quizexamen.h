#ifndef QUIZEXAMEN_H
#define QUIZEXAMEN_H

#include <QDialog>
#include "quiz.h"  // Assuming you have a Quiz class with a method getQuestions()

namespace Ui {
class QuizExamen;
}

class QuizExamen : public QDialog
{
    Q_OBJECT

public:
    explicit QuizExamen(Quiz *quiz, QWidget *parent = nullptr);
    ~QuizExamen();


private:
    Ui::QuizExamen *ui;
    Quiz *quiz;
    void displayQuestions();
    int currentQuestionIndex;
    int *userAnswers;

};

#endif // QUIZEXAMEN_H
