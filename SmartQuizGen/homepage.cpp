extern "C" {
#include <Python.h>
}
#include "homepage.h"


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




    // connect(ui->GenerateFromOldButton, &QPushButton::clicked, this, [this]() {
    //     if (!generateAllowed) {
    //         QMessageBox::warning(this, "Input Error", "You Should Upload First A PDF");
    //         return;
    //     }
    //     QString currentDir = QCoreApplication::applicationDirPath();
    //     qDebug() << currentDir;


    //     QString pythonExecutable = currentDir + "/../../../../Script/.venv/Scripts/python.exe";
    //     QString scriptPath = currentDir + "/../../../../Script/.venv/Scripts/main.py";

    //     QProcess process;
    //     process.setProgram(pythonExecutable);
    //     qDebug() << uploadedFilePath;
    //     process.setArguments(QStringList() << scriptPath << uploadedFilePath);

    //     process.setWorkingDirectory(currentDir + "/../../../../Script/.venv/Scripts");

    //     process.start();

    //     if (!process.waitForFinished()) {
    //         qDebug() << "Failed to run Python script!";
    //         qDebug() << "Error: " << process.errorString();
    //         QMessageBox::critical(this, "Execution Error", "An error occurred while running the Python script:\n" + process.errorString());
    //         return;  // Stop the rest of the procedure
    //     } else {
    //         qDebug() << "Python script executed successfully.";
    //         jsonQuizData = process.readAllStandardOutput();
    //         jsonQuizData = jsonQuizData.replace("\r", "");
    //         jsonQuizData = jsonQuizData.replace("```json", "");
    //         jsonQuizData = jsonQuizData.replace("```", "");
    //         jsonQuizData = jsonQuizData.trimmed();

    //         QJsonDocument doc = QJsonDocument::fromJson(jsonQuizData.toUtf8());
    //         if (doc.isNull()) {
    //             qDebug() << "Failed to parse the JSON output.";
    //             QMessageBox::critical(this, "JSON Parse Error", "Failed to parse the JSON output from the script.");
    //             return;  // Stop the rest of the procedure
    //         }

    //         // Check if there's an error field in the JSON
    //         QJsonObject jsonObject = doc.object();
    //         if (jsonObject.contains("error") && jsonObject["error"].isNull()) {
    //             QJsonArray quizArray = jsonObject["quiz"].toArray();
    //             Quiz quiz;  // Create a new Quiz object
    //             for (const QJsonValue &value : quizArray) {
    //                 QJsonObject questionObject = value.toObject();
    //                 QString correctAnswer = questionObject["correct_answer"].toString();
    //                 QJsonArray options = questionObject["options"].toArray();
    //                 QString questionText = questionObject["question"].toString();

    //                 // Convert QJsonArray options to std::vector<QString>
    //                 std::vector<QString> optionsList;
    //                 for (const QJsonValue &option : options) {
    //                     optionsList.push_back(option.toString());
    //                 }

    //                 // Create a Question object and add it to the Quiz
    //                 Question question(questionText, optionsList, correctAnswer);
    //                 quiz.addQuestion(question);
    //             }

    //             // Save the processed quiz data to a file
    //             QString outputFilePath = "C:/Users/PC/Desktop/pdf cpp project/TheQuiz/quiz.json";
    //             if(!outputFilePath.isEmpty()){
    //                 QFile file(outputFilePath);
    //                 if (file.open(QIODevice::WriteOnly)) {
    //                     QTextStream out(&file);
    //                     out << doc.toJson(QJsonDocument::Indented);
    //                     file.close();
    //                     qDebug() << "JSON file saved successfully.";
    //                     qDebug() << "Quiz Questions:";

    //                     QuizExamen *quizWindow = new QuizExamen(currentUser,&quiz, this);
    //                     quizWindow->show();
    //                     this->hide();
    //                     QMessageBox::information(quizWindow, "Success", "🎉 Quiz Generated !");
    //                 } else {
    //                     qDebug() << "Failed to open the file for writing.";
    //                     QMessageBox::critical(this, "File Error", "Failed to open the file for writing the quiz.");
    //                     return;  // Stop the rest of the procedure
    //                 }
    //             } else {
    //                 qDebug() << "No file selected for saving.";
    //                 QMessageBox::warning(this, "Save Error", "No file selected for saving the quiz.");
    //                 return;  // Stop the rest of the procedure
    //             }
    //         } else {
    //             qDebug() << "Error in JSON data: " << jsonObject["error"].toString();
    //             QMessageBox::critical(this, "JSON Error", "There was an error in the JSON data.\n" + jsonObject["error"].toString());
    //             return;  // Stop the rest of the procedure
    //         }
    //     }
    // });



}

HomePage::~HomePage() {
    delete ui;
}
