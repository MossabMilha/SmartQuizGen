#include "showpdfs.h"
#include "ui_showpdfs.h"


ShowPdfs::ShowPdfs(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowPdfs)
    , currentUser(user)
{
    ui->setupUi(this);

    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    loadPdfs(currentUser);
}
void ShowPdfs::loadPdfs(User* user)
{
    int userId = user->getId();
    std::vector<pdf> userPdfs = pdf::getPdfsOfUser(userId);

    if (container) {
        delete container; // delete the previous container and its layout
        container = nullptr;
    }

    container = new QWidget(this);
    layout = new QVBoxLayout(container);

    for (const auto& pdf : userPdfs) {
        QWidget* pdfWidget = new QWidget(this);
        QHBoxLayout* hLayout = new QHBoxLayout(pdfWidget);

        QLabel* pdfLabel = new QLabel(
            QString::fromStdString(pdf.getFilename()) + "\nUploaded at: " +
                QString::fromStdString(pdf.getuploaded_at()),
            pdfWidget
            );

        QPushButton* actionButton = new QPushButton(
            pdf::pdfHaveQuiz(pdf.getId()) ? "Generate New Quiz" : "Generate Quiz",
            pdfWidget
            );
        actionButton->setFixedWidth(150);

        connect(actionButton, &QPushButton::clicked, this, [this, pdf,userId]() {
            QString output = homePageFunctions::GenerateQuiz(pdf.getId());
            if (output == "Quiz generation completed successfully.") {
                QMessageBox::information(this, "Success", output);
                User c_user = User::getUserById(userId);
                this->loadPdfs(&c_user);
            } else {
                QMessageBox::critical(this, "Error", output);
            }
        });

        hLayout->addWidget(pdfLabel);
        hLayout->addWidget(actionButton);
        hLayout->setAlignment(Qt::AlignLeft);

        pdfWidget->setLayout(hLayout);
        layout->addWidget(pdfWidget);
    }

    container->setLayout(layout);
    scrollArea->setWidget(container);
}

ShowPdfs::~ShowPdfs()
{

    delete ui;
}
