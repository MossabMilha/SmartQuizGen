    #include "quizexamen.h"
#include "ui_quizexamen.h"
#include <QDebug>
#include <QMessageBox>
#include "homepage.h"


void QuizExamen::saveCurrentAnswer() {
    if (ui->Answer1->isChecked()) userAnswers[currentQuestionIndex] = 0;
    else if (ui->Answer2->isChecked()) userAnswers[currentQuestionIndex] = 1;
    else if (ui->Answer3->isChecked()) userAnswers[currentQuestionIndex] = 2;
    else if (ui->Answer4->isChecked()) userAnswers[currentQuestionIndex] = 3;
}

void QuizExamen::displayQuestion(const Question& question) {
    ui->Question->setText(question.getText());
    const std::vector<QString>& opts = question.getOptions();
    ui->Answer1->setText(opts[0]);
    ui->Answer2->setText(opts[1]);
    ui->Answer3->setText(opts[2]);
    ui->Answer4->setText(opts[3]);


    ui->Answer1->setAutoExclusive(false);
    ui->Answer2->setAutoExclusive(false);
    ui->Answer3->setAutoExclusive(false);
    ui->Answer4->setAutoExclusive(false);
    ui->Answer1->setChecked(false);
    ui->Answer2->setChecked(false);
    ui->Answer3->setChecked(false);
    ui->Answer4->setChecked(false);
    ui->Answer1->setAutoExclusive(true);
    ui->Answer2->setAutoExclusive(true);
    ui->Answer3->setAutoExclusive(true);
    ui->Answer4->setAutoExclusive(true);


    int previous = userAnswers[currentQuestionIndex];
    if (previous == 0) ui->Answer1->setChecked(true);
    else if (previous == 1) ui->Answer2->setChecked(true);
    else if (previous == 2) ui->Answer3->setChecked(true);
    else if (previous == 3) ui->Answer4->setChecked(true);
}

void QuizExamen::updateNavigationButtons(int totalQuestions) {
    ui->PreviousButton->setVisible(currentQuestionIndex > 0);
    ui->NextButton->setVisible(currentQuestionIndex < totalQuestions - 1);
    ui->SubmitButton->setVisible(currentQuestionIndex == totalQuestions - 1);
}

QuizExamen::QuizExamen(User *user, Quiz *quiz, QWidget *parent)
    : QDialog(parent), ui(new Ui::QuizExamen), quiz(quiz), currentUser(user)
{
    int userId = currentUser->getId();
    ui->setupUi(this);
    std::vector<Question> questions = quiz->getQuestions();
    currentQuestionIndex = 0;
    userAnswers = new int[questions.size()]();

    displayQuestion(questions[currentQuestionIndex]);
    updateNavigationButtons(questions.size());

    connect(ui->NextButton, &QPushButton::clicked, this, [=]() {
        saveCurrentAnswer();
        currentQuestionIndex++;
        displayQuestion(questions[currentQuestionIndex]);
        updateNavigationButtons(questions.size());
    });

    connect(ui->PreviousButton, &QPushButton::clicked, this, [=]() {
        saveCurrentAnswer();
        currentQuestionIndex--;
        displayQuestion(questions[currentQuestionIndex]);
        updateNavigationButtons(questions.size());
    });

    connect(ui->SubmitButton, &QPushButton::clicked, this, [=]() {
        User user = User::getUserById(userId);
        saveCurrentAnswer();
        int correctAnswers = 0;
        for (size_t i = 0; i < questions.size(); i++) {
            qDebug()<<"=="<<questions[i].getOptions()[userAnswers[i]];
            qDebug()<<"="<<questions[i].getCorrectAnswer();

            if (questions[i].getOptions()[userAnswers[i]] == questions[i].getCorrectAnswer()) {
                correctAnswers++;
            }
        }

        HomePage* homePage = new HomePage(&user);
        homePage->show();
        this->hide();

        QMessageBox::information(homePage, "Quiz Result",
                                 QString("You got %1 out of %2 questions correct!")
                                     .arg(correctAnswers)
                                     .arg(questions.size()));
    });
}

QuizExamen::~QuizExamen()
{
    delete ui;

}


