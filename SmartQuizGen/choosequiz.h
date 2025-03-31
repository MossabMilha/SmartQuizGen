#ifndef CHOOSEQUIZ_H
#define CHOOSEQUIZ_H

#include <QDialog>
#include "user.h"

namespace Ui {
class ChooseQuiz;
}

class ChooseQuiz : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseQuiz(User* user, QWidget *parent = nullptr);
    ~ChooseQuiz();

private:
    Ui::ChooseQuiz *ui;
};

#endif // CHOOSEQUIZ_H
