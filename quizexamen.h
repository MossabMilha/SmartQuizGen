#ifndef QUIZEXAMEN_H
#define QUIZEXAMEN_H

#include <QDialog>

namespace Ui {
class QuizExamen;
}

class QuizExamen : public QDialog
{
    Q_OBJECT

public:
    explicit QuizExamen(QWidget *parent = nullptr);
    ~QuizExamen();

private:
    Ui::QuizExamen *ui;
};

#endif // QUIZEXAMEN_H
