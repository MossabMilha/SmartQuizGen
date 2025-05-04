#include "showpdfs.h"
#include "ui_showpdfs.h"
#include "homepage.h"
#include <QMessageBox>

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

    // Set the container as the widget of the scroll area
    ui->scrollArea->setWidget(container);

    // Set window title with username
    QString username = user->getUsername();
    QString qTitle = QString("PDFs - ") + username;
    setWindowTitle(qTitle);


    // Load the PDFs
    loadPdfs(currentUser);

    // Apply styling to the Back Home button
    ui->BackHomePage->setStyleSheet("background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #4C9CC0, stop:1 #0D3D56); color: white; border: none; border-radius: 4px; padding: 8px; font-weight: bold;");

    // Handle back button
    connect(ui->BackHomePage, &QPushButton::clicked, this, [=]() {
        User user = User::getUserById(userId);
        HomePage* Home = new HomePage(&user);
        Home->show();
        this->close();  // Changed from hide() to close() to properly release resources
    });
}

void ShowPdfs::loadPdfs(User* user)
{
    int userId = user->getId();
    std::vector<pdf> userPdfs = pdf::getPdfsOfUser(userId);

    // Clear existing widgets from layout
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    // Set the container's background to transparent
    container->setStyleSheet("background-color: transparent;");

    // If no PDFs, show message
    if (userPdfs.empty()) {
        QLabel* noPdfsLabel = new QLabel("You haven't uploaded any PDFs yet.", container);
        noPdfsLabel->setAlignment(Qt::AlignCenter);
        noPdfsLabel->setStyleSheet("font-size: 12pt; color: #0D3D56; padding: 20px;");
        layout->addWidget(noPdfsLabel);
    } else {

        for (const auto& pdf : userPdfs) {
            QWidget* pdfWidget = new QWidget(container);
            pdfWidget->setStyleSheet("background-color: transparent; border-radius: 0px; padding: 15px 20px; margin: 0px;");

            QHBoxLayout* hLayout = new QHBoxLayout(pdfWidget);
            hLayout->setContentsMargins(0, 0, 0, 0);
            hLayout->setSpacing(5); // Optional: add spacing between label and button

            QLabel* pdfLabel = new QLabel(
                QString::fromStdString(pdf.getFilename()) + "\nUploaded at: " +
                    QString::fromStdString(pdf.getuploaded_at()),
                pdfWidget
                );
            pdfLabel->setWordWrap(true);
            pdfLabel->setStyleSheet("color: #0D3D56; font-size: 10pt;");

            QPushButton* actionButton = new QPushButton("Generate New Quiz", pdfWidget);
            actionButton->setFixedSize(150, 24); // Width and smaller height
            actionButton->setFixedSize(150, 32);  // Slightly taller for text visibility
            actionButton->setStyleSheet(
                "background-color: #4C9CC0;"
                "color: white;"
                "border: none;"
                "border-radius: 4px;"
                "font-weight: bold;"
                "font-size: 10pt;"
                "padding: 4px 8px;"
                );

            connect(actionButton, &QPushButton::clicked, this, [=]() {
                QApplication::setOverrideCursor(Qt::WaitCursor);
                actionButton->setEnabled(false);
                actionButton->setText("Generating...");

                QString output = homePageFunctions::GenerateQuiz(pdf.getId());

                QApplication::restoreOverrideCursor();

                if (output == "Quiz generation completed successfully.") {
                    QMessageBox::information(this, "Success", output);
                    User c_user = User::getUserById(userId);
                    this->loadPdfs(&c_user);
                } else {
                    QMessageBox::critical(this, "Error", output);
                    actionButton->setEnabled(true);
                    actionButton->setText(pdf::pdfHaveQuiz(pdf.getId()) ? "Generate New Quiz" : "Generate Quiz");
                }
            });

            hLayout->addWidget(pdfLabel,1);
            hLayout->addWidget(actionButton, 0);
            pdfWidget->setLayout(hLayout);
            layout->addWidget(pdfWidget);
        }

    }

    // Add stretch to push all widgets to the top
    layout->addStretch();
}

ShowPdfs::~ShowPdfs()
{
    delete ui;
}
