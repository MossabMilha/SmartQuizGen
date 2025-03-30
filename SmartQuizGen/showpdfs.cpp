#include "showpdfs.h"
#include "ui_showpdfs.h"
#include "pdf.h"
#include <QDebug>
ShowPdfs::ShowPdfs(User* user, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ShowPdfs)
{

    qDebug()<<user->getId();
    std::vector<pdf> userPdf = pdf::getPdfsOfUser(user->getId());

    qDebug() << "User PDFs:";
    for (const auto& pdfEntry : userPdf) {
        qDebug() << QString::fromStdString(pdfEntry.getFilename());
    }
    ui->setupUi(this);
}

ShowPdfs::~ShowPdfs()
{

    delete ui;
}
