#include "choosequiz.h"
#include "pdf.h"
#include "ui_choosequiz.h"
#include "quiz.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
ChooseQuiz::ChooseQuiz(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChooseQuiz)
{

    std::vector<Quiz> userQuizs = Quiz::getQuizsByUserId(user->getId());
    qDebug() << "Number of quizzes: " << userQuizs.size();

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (const auto& quiz : userQuizs) {

        QWidget* quizWidget = new QWidget(this);  // Changed variable name to quizWidget
        QVBoxLayout* vLayout = new QVBoxLayout(quizWidget);  // Using a vertical layout to display all the info

        QLabel* quizIdLabel = new QLabel("Quiz ID: " + QString::number(quiz.getId()), quizWidget);

        QLabel* pdfLabel = new QLabel("PDF: " + QString::fromStdString(pdf::getFilenameByPdfID(quiz.getPdfId())), quizWidget);

        QLabel* createdAtLabel = new QLabel("Created At: " + quiz.getCreatedAt(), quizWidget);

        QPushButton* passQuizButton = new QPushButton("Pass the Quiz", quizWidget);
        passQuizButton->setFixedWidth(200);

        connect(passQuizButton, &QPushButton::clicked, this, [this, quiz]() {
            qDebug()<<quiz.getId();
        });

        // Add widgets to layout
        vLayout->addWidget(quizIdLabel);
        vLayout->addWidget(pdfLabel);
        vLayout->addWidget(createdAtLabel);
        vLayout->addWidget(passQuizButton);

        // Set layout and add quizWidget to the main layout
        quizWidget->setLayout(vLayout);
        layout->addWidget(quizWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Add scroll area to the main layout
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

}

ChooseQuiz::~ChooseQuiz()
{
    delete ui;
}
