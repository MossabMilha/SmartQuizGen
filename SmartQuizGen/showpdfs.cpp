#include "showpdfs.h"
#include "ui_showpdfs.h"

ShowPdfs::ShowPdfs(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowPdfs)
    , currentUser(user)
{
    int userId = currentUser->getId();
    ui->setupUi(this);

    // Prepare the layout to hold the PDF widgets
    layout = new QVBoxLayout();

    // Create a container widget to hold the layout
    container = new QWidget(this);
    container->setLayout(layout);

    // Set the container as the widget of the scroll area defined in the .ui
    ui->scrollArea->setWidget(container);

    // Load the PDFs
    loadPdfs(currentUser);

    // Handle back button
    connect(ui->BackHomePage, &QPushButton::clicked, this, [=]() {
        User user = User::getUserById(userId);
        HomePage* Home = new HomePage(&user);
        Home->show();
        this->hide();
    });
}

void ShowPdfs::loadPdfs(User* user)
{
    int userId = user->getId();
    std::vector<pdf> userPdfs = pdf::getPdfsOfUser(userId);


    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }


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

        connect(actionButton, &QPushButton::clicked, this, [this, pdf, userId]() {
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

    layout->addStretch();
}

ShowPdfs::~ShowPdfs()
{
    delete ui;
}
