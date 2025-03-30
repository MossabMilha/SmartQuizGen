#ifndef HOMEPAGEFUNCTIONS_H
#define HOMEPAGEFUNCTIONS_H
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include "user.h"
#include "pdf.h"

class homePageFunctions
{
public:
    homePageFunctions();
    static QString uploadpdf(int userId, QString filePath, int* pdfId = nullptr);
    static QString Generatepdf(int userId,QString filePath);
    static QString GenerateQuiz(int pdfId);


};

#endif
