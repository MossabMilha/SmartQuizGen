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
    container->setStyleSheet("background-color: transparent;");
    QVBoxLayout* layout = new QVBoxLayout(container);
    layout->setSpacing(15);
    layout->setContentsMargins(15, 15, 15, 15);

    // If no quizzes, show message
    if (userQuizs.empty()) {
        QLabel* noQuizzesLabel = new QLabel("No quizzes available yet.\nGenerate a quiz from your PDFs first!", container);
        noQuizzesLabel->setAlignment(Qt::AlignCenter);
        noQuizzesLabel->setStyleSheet(
            "font-size: 14pt; "
            "color: #0D3D56; "
            "padding: 40px; "
            "font-weight: bold; "
            "text-align: center;"
            );
        noQuizzesLabel->setWordWrap(true);
        layout->addWidget(noQuizzesLabel);
    } else {
        for (const auto& quiz : userQuizs) {
            // Create main quiz widget container
            QWidget* quizWidget = new QWidget(container);
            quizWidget->setStyleSheet(
                "QWidget {"
                "    background-color: rgba(255, 255, 255, 0.8);"
                "    border: 2px solid #B8DCF0;"
                "    border-radius: 12px;"
                "    padding: 20px;"
                "    margin: 5px;"
                "}"
                "QWidget:hover {"
                "    background-color: rgba(255, 255, 255, 0.95);"
                "    border: 2px solid #4C9CC0;"
                "    transform: translateY(-2px);"
                "}"
                );

            QVBoxLayout* vLayout = new QVBoxLayout(quizWidget);
            vLayout->setSpacing(10);
            vLayout->setContentsMargins(15, 15, 15, 15);

            // Quiz ID label with enhanced styling
            QLabel* quizIdLabel = new QLabel("Quiz #" + QString::number(quiz.getId()), quizWidget);
            quizIdLabel->setStyleSheet(
                "color: #005571; "
                "font-size: 14pt; "
                "font-weight: bold; "
                "margin-bottom: 8px; "
                "padding: 5px 10px; "
                "background-color: rgba(76, 156, 192, 0.1); "
                "border-radius: 15px;"
                );
            quizIdLabel->setAlignment(Qt::AlignCenter);

            // PDF label with icon-like styling
            QLabel* pdfLabel = new QLabel("📄 " + QString::fromStdString(pdf::getFilenameByPdfID(quiz.getPdfId())), quizWidget);
            pdfLabel->setStyleSheet(
                "color: #0D3D56; "
                "font-size: 11pt; "
                "font-weight: 600; "
                "margin: 5px 0px; "
                "padding: 8px 12px; "
                "background-color: rgba(223, 241, 255, 0.5); "
                "border-radius: 8px; "
                "border-left: 4px solid #4C9CC0;"
                );
            pdfLabel->setWordWrap(true);

            // Created date label
            QLabel* createdAtLabel = new QLabel("🕒 Created: " + quiz.getCreatedAt(), quizWidget);
            createdAtLabel->setStyleSheet(
                "color: #5A7A8A; "
                "font-size: 10pt; "
                "margin: 5px 0px; "
                "padding: 6px 12px; "
                "font-style: italic;"
                );

            // Enhanced Pass Quiz button
            QPushButton* passQuizButton = new QPushButton("🎯 Take This Quiz", quizWidget);
            passQuizButton->setFixedSize(220, 65);
            passQuizButton->setStyleSheet(
                "QPushButton {"
                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                "                                stop:0 #4C9CC0, stop:0.5 #2E7A99, stop:1 #0D3D56);"
                "    color: white;"
                "    border: none;"
                "    border-radius: 22px;"
                "    font-weight: bold;"
                "    font-size: 12pt;"
                "    padding: 12px 20px;"
                "    margin-top: 10px;"
                "}"
                "QPushButton:hover {"
                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                "                                stop:0 #5AADD0, stop:0.5 #3E8AA9, stop:1 #1A4D66);"
                "    transform: scale(1.05);"
                "}"
                "QPushButton:pressed {"
                "    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, "
                "                                stop:0 #3A8CB0, stop:0.5 #2E6A89, stop:1 #0A2D46);"
                "    transform: scale(0.98);"
                "}"
                );

            // Connect button with same functionality
            connect(passQuizButton, &QPushButton::clicked, this, [this, quizCopy = quiz, userId]() {
                User c_user = User::getUserById(userId);
                QuizExamen* QuizExamenPage = new QuizExamen(&c_user, new Quiz(quizCopy));
                QuizExamenPage->show();
                this->hide();
            });

            // Add widgets to layout
            vLayout->addWidget(quizIdLabel);
            vLayout->addWidget(pdfLabel);
            vLayout->addWidget(createdAtLabel);
            vLayout->addWidget(passQuizButton, 0, Qt::AlignCenter);

            quizWidget->setLayout(vLayout);
            layout->addWidget(quizWidget);
        }
    }

    // Add stretch to push content to top
    layout->addStretch();

    container->setLayout(layout);
    ui->scrollArea->setWidget(container);

    // Back button connection remains the same
    connect(ui->BackHomePage, &QPushButton::clicked, this, [this, userId]() {
        User user = User::getUserById(userId);
        HomePage* Home = new HomePage(&user);
        Home->show();
        this->hide();
    });
}

ChooseQuiz::~ChooseQuiz()
{
    delete ui;
}
