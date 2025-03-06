#include "quizexamen.h"
#include "ui_quizexamen.h"

QuizExamen::QuizExamen(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::QuizExamen)
{
    ui->setupUi(this);
}

QuizExamen::~QuizExamen()
{
    delete ui;
}
