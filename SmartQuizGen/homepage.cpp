extern "C" {
#include <Python.h>
}
#include "homepage.h"
#include "showpdfs.h"
#include "choosequiz.h"


QString jsonQuizData; // Variable to store JSON before saving

void parseJsonQuiz(const QString& jsonString, Quiz& quiz){
    QJsonDocument doc = QJsonDocument::fromJson(jsonString.toUtf8());
    if(!doc.isNull()){
        QJsonObject quizObject = doc.object();
        QJsonArray quizArray = quizObject["quiz"].toArray();
        for (const QJsonValue& value : quizArray) {
            QJsonObject questionObj = value.toObject();
            QString questionText = questionObj["question"].toString();
            QJsonArray optionsArray = questionObj["options"].toArray();
            QString correctAnswer = questionObj["correct_answer"].toString();

            std::vector<QString> options;
            for (const QJsonValue& optionValue : optionsArray) {
                options.push_back(optionValue.toString());
            }

            Question question(questionText, options, correctAnswer);
            quiz.addQuestion(question);
        }
    } else {
        qWarning() << "Failed to parse JSON.";
    }
}

HomePage::HomePage(User* user, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HomePage),
    currentUser(user),
    uploadedFilePath("")

{
    ui->setupUi(this);
    ui->UsernameTitle->setText(currentUser->getUsername());

    int userId =User::getId(currentUser->getUsername());

    connect(ui->UploadAndGenerateButton, &QPushButton::clicked, this, [this, userId]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open PDF", "", "PDF Files (*.pdf)");
        if (filePath.isEmpty()) {
            return;
        }

        QString output = homePageFunctions::Generatepdf(userId, filePath);

        if (output == "Quiz generation completed successfully.") {
            QMessageBox::information(this, "Success", output);
        } else {
            QMessageBox::critical(this, "Error", output);
        }
    });

    connect(ui->UploadButton, &QPushButton::clicked, this, [this, userId]() {
        QString filePath = QFileDialog::getOpenFileName(this, "Open PDF", "", "PDF Files (*.pdf)");
        QString output;
        if (!filePath.isEmpty()) {
            output = homePageFunctions::uploadpdf(userId, filePath, nullptr);  // Adjusted to pass nullptr to indicate not modifying pdfId
        }
        if (output == "PDF successfully saved to the database.") {
            QMessageBox::information(this, "Success", output);
        } else {
            QMessageBox::critical(this, "Error", output);
        }
    });

    connect(ui->GenerateFromOldButton, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        ShowPdfs* ShowPdfsPage = new ShowPdfs(&user);
        ShowPdfsPage->show();
        this->hide();
    });

    connect(ui->PassQuizButton, &QPushButton::clicked, this, [this,userId]() {
        User user = User::getUserById(userId);
        ChooseQuiz* ChooseQuizPage = new ChooseQuiz(&user);
        ChooseQuizPage->show();
        this->hide();
    });




}

HomePage::~HomePage() {
    delete ui;
}
