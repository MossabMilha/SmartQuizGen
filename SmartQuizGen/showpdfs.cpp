#include "showpdfs.h"
#include "ui_showpdfs.h"
#include "pdf.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>

ShowPdfs::ShowPdfs(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowPdfs)
{
    ui->setupUi(this);

    qDebug() << "User ID: " << user->getId();

    std::vector<pdf> userPdfs = pdf::getPdfsOfUser(user->getId());

    QVBoxLayout* mainLayout = new QVBoxLayout(this);


    QScrollArea* scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);


    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(container);

    for (const auto& pdf : userPdfs) {
        QWidget* pdfWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(pdfWidget);

        QLabel* pdfLabel = new QLabel(QString::fromStdString(pdf.getFilename()), pdfWidget);
        QPushButton* quizButton = new QPushButton(pdf::pdfHaveQuiz(pdf.getId()) ? "New Quiz" : "Generate Quiz", pdfWidget);
        quizButton->setFixedWidth(200);


        QHBoxLayout* buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(quizButton);
        buttonLayout->setAlignment(Qt::AlignCenter);

        if (pdf::pdfHaveQuiz(pdf.getId())) {
            QPushButton* passQuizButton = new QPushButton("Pass Quiz", pdfWidget);
            passQuizButton->setFixedWidth(100);
            quizButton->setFixedWidth(100);

            buttonLayout->addWidget(passQuizButton);

            connect(passQuizButton, &QPushButton::clicked, this, [this, pdf]() {
                qDebug() << "Passing quiz for: " << pdf.getId();
            });
        }

        connect(quizButton, &QPushButton::clicked, this, [this, pdf]() {
            qDebug() << "Generating quiz for: " << pdf.getId();
        });


        hLayout->addWidget(pdfLabel);
        hLayout->addLayout(buttonLayout);
        hLayout->setSpacing(10);
        hLayout->setAlignment(Qt::AlignLeft);

        pdfWidget->setLayout(hLayout);
        layout->addWidget(pdfWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);

    // Add scroll area to the main layout
    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);
}

ShowPdfs::~ShowPdfs()
{

    delete ui;
}
