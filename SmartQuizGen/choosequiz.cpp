#include "choosequiz.h"
#include "ui_choosequiz.h"

#include "pdf.h"
#include "quiz.h"
#include "quizexamen.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

ChooseQuiz::ChooseQuiz(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseQuiz)
{
    ui->setupUi(this);

    int userId = user->getId();
    std::vector<Quiz> userQuizs = Quiz::getQuizsByUserId(userId);
    qDebug() << "Number of quizzes: " << userQuizs.size();

    // Prepare layout for scroll area content
    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (const auto& quiz : userQuizs) {
        QWidget* quizWidget = new QWidget(container);
        QVBoxLayout* vLayout = new QVBoxLayout(quizWidget);

        QLabel* quizIdLabel = new QLabel("Quiz ID: " + QString::number(quiz.getId()), quizWidget);
        QLabel* pdfLabel = new QLabel("PDF: " + QString::fromStdString(pdf::getFilenameByPdfID(quiz.getPdfId())), quizWidget);
        QLabel* createdAtLabel = new QLabel("Created At: " + quiz.getCreatedAt(), quizWidget);

        QPushButton* passQuizButton = new QPushButton("Pass the Quiz", quizWidget);
        passQuizButton->setFixedWidth(200);

        connect(passQuizButton, &QPushButton::clicked, this, [this, quizCopy = quiz, userId]() {
            User c_user = User::getUserById(userId);
            QuizExamen* QuizExamenPage = new QuizExamen(&c_user, new Quiz(quizCopy));
            QuizExamenPage->show();
            this->hide();
        });

        vLayout->addWidget(quizIdLabel);
        vLayout->addWidget(pdfLabel);
        vLayout->addWidget(createdAtLabel);
        vLayout->addWidget(passQuizButton);
        quizWidget->setLayout(vLayout);
        layout->addWidget(quizWidget);
    }

    container->setLayout(layout);
    ui->scrollArea->setWidget(container);


    connect(ui->BackHomePage, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        HomePage* Home = new HomePage(&user);
        Home->show();
        this->hide();;
    });
}

ChooseQuiz::~ChooseQuiz()
{
    delete ui;
}
