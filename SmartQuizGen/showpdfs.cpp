#include "showpdfs.h"
#include "ui_showpdfs.h"
#include "pdf.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include "homepagefunctions.h"
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

        connect(quizButton, &QPushButton::clicked, this, [this, pdf]() {
            if(homePageFunctions::GenerateQuiz(pdf.getId()) == "Quiz generation completed successfully.") {
                User user = User::getUserById(pdf.getUserId());
                ShowPdfs* ShowPdfsPage = new ShowPdfs(&user);
                QMessageBox::information(this, "Success", "Quiz generation completed successfully.");
                ShowPdfsPage->show();
                this->hide();
            } else {
                QMessageBox::critical(this, "Error", homePageFunctions::GenerateQuiz(pdf.getId()));
            }
        });

        hLayout->addWidget(pdfLabel);
        hLayout->addWidget(quizButton);  // Fixed the issue of missing button alignment
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
