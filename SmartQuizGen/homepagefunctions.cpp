#include "homepagefunctions.h"




QString homePageFunctions::uploadpdf(int userId, QString filePath, int* pdfId) {
    if (userId != -1) {
        pdf newpdf(userId, filePath.toStdString());

        if (pdfId == nullptr) {
            // If pdfId is nullptr (default), just save the PDF but don't modify pdfId
            if (newpdf.savePdfToDb()) {
                return "PDF successfully saved to the database.";
            }
        } else {
            // If pdfId is not nullptr, save the PDF and update pdfId with the newly inserted ID
            if (newpdf.savePdfToDb(*pdfId)) {
                return "PDF successfully saved to the database.";
            }
        }

        return "Failed to save PDF to the database.";
    } else {
        return "User not found.";
    }
}
QString homePageFunctions::Generatepdf(int userId, QString filePath) {
    int pdfId = -1;
    QString output = homePageFunctions::uploadpdf(userId, filePath, &pdfId);


    if (output == "PDF successfully saved to the database.") {
        QProcess process;
        QString currentDir = QCoreApplication::applicationDirPath();
        QString pythonExecutable = currentDir + "/../../../../Script/.venv/Scripts/python.exe";
        QString scriptPath = currentDir + "/../../../../Script/main.py";

        QStringList arguments;
        arguments << scriptPath << QString::number(pdfId);
        process.start(pythonExecutable, arguments);

        if (!process.waitForFinished()) {
            qDebug() << "Error:" << process.errorString();
            return "Error: Python script execution failed.";
        } else {
            QString output = process.readAllStandardOutput();
            QString error = process.readAllStandardError();

            qDebug() << "Output:" << output;
            qDebug() << "Error:" << error;

            if (!error.isEmpty()) {
                return "Python script executed with errors: " + error;
            } else {
                return "Quiz generation completed successfully.";
            }
        }
    } else {
        return output;
    }
}
QString homePageFunctions::GenerateQuiz(int pdfId) {
    QProcess process;
    QString currentDir = QCoreApplication::applicationDirPath();
    QString pythonExecutable = currentDir + "/../../../../Script/.venv/Scripts/python.exe";
    QString scriptPath = currentDir + "/../../../../Script/main.py";
    QStringList arguments;
    arguments << scriptPath << QString::number(pdfId);
    process.start(pythonExecutable, arguments);

    if (!process.waitForFinished()) {
        qDebug() << "Error:" << process.errorString();
        return "Error: Python script execution failed.";
    } else {
        QString output = process.readAllStandardOutput();
        QString error = process.readAllStandardError();

        qDebug() << "Output:" << output;
        qDebug() << "Error:" << error;

        if (!error.isEmpty()) {
            return "Python script executed with errors: " + error;
        } else {
            return "Quiz generation completed successfully.";
        }
    }
}



homePageFunctions::homePageFunctions() {}
