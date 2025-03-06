extern "C" {
#include <Python.h>
}
#include "HomePage.h"
#include "ui_HomePage.h"
#include "quizexamen.h"

#include "user.h"
#include "quiz.h"
#include "question.h"

#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPixmap>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <iostream>
#include <QProcess>
#include <QFile>

void parseJsonQuiz(const QString& jsonString,Quiz& quiz){
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
    }else{
        qWarning() << "Failed to parse JSON.";
    }


}
HomePage::HomePage(User* user, QWidget *parent) :
    QDialog(parent),  // Change QWidget to QDialog
    ui(new Ui::HomePage),
    currentUser(user)
{
    ui->setupUi(this);
    ui->UsernameTitle->setText(currentUser->getUsername());
    QPixmap pixmap("C:/Users/PC/Desktop/SmartQuizGen/images/UploadImage.svg");  // Specify the image path
    ui->UploadImage->setPixmap(pixmap);
    ui->UploadImage->setScaledContents(true);

    connect(ui->UploadFileButton, &QPushButton::clicked, this, [this]() {  // Capture 'this' instead of [&]
        // Open the file dialog to select a PDF
        QString filePath = QFileDialog::getOpenFileName(this, "Open PDF", "", "PDF Files (*.pdf)");

        if (!filePath.isEmpty()) {
            qDebug() << "File chosen:" << filePath;
            generateAllowed = true;  // Update member variable
        }
    });

    connect(ui->pushButton, &QPushButton::clicked, this, [this]() {  // Capture 'this'
        if (!generateAllowed) {  // Now uses member variable
            QMessageBox::warning(this, "Input Error", "You Should Upload First A PDF");
            return;
        }

        QString pythonExecutable = "C:/Users/PC/Desktop/pdf cpp project/python script/.venv/Scripts/python.exe";
        QString scriptPath = "C:/Users/PC/Desktop/pdf cpp project/python script/main.py";

        QProcess process;
        process.setProgram(pythonExecutable);
        process.setArguments(QStringList() << scriptPath);
        process.setWorkingDirectory("C:/Users/PC/Desktop/pdf cpp project/python script"); // Set working dir

        process.start();

        if (!process.waitForFinished()) {
            qDebug() << "Failed to run Python script!";
            qDebug() << "Error: " << process.errorString();
        } else {
            qDebug() << "Python script executed successfully.";
            QString jsonOutput = process.readAllStandardOutput();
            jsonOutput = jsonOutput.replace("\r", "");
            jsonOutput = jsonOutput.replace("```json", "");
            jsonOutput = jsonOutput.replace("```", "");
            jsonOutput = jsonOutput.trimmed();
            qDebug() << "Output: " << jsonOutput;

            Quiz quiz;
            parseJsonQuiz(jsonOutput,quiz);
            qDebug() << "Output Quiz format: ";
            QJsonDocument doc = QJsonDocument::fromJson(jsonOutput.toUtf8());
            if (doc.isNull()) {
                qDebug() << "Failed to parse the JSON output.";
            } else {
                qDebug() << "Valid JSON Output: ";
                qDebug() << doc.toJson(QJsonDocument::Indented);
                QString outputFilePath = "C:/Users/PC/Desktop/pdf cpp project/TheQuiz/quiz.json";
                if(!outputFilePath.isEmpty()){
                    QFile file(outputFilePath);
                    if (file.open(QIODevice::WriteOnly)) {
                        QTextStream out(&file);
                        out << doc.toJson(QJsonDocument::Indented);
                        file.close();
                        qDebug() << "JSON file saved successfully.";
                        QuizExamen *quizWindow = new QuizExamen(this);
                        quizWindow->show();
                        QMessageBox::information(this, "Success", "🎉 Quiz Generated !");
                        this->hide();

                    } else {
                        qDebug() << "Failed to open the file for writing.";
                    }
                }else {
                    qDebug() << "No file selected for saving.";
                }

            }
        }
    });
}

HomePage::~HomePage() {
    delete ui;
}
