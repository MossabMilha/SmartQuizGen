#ifndef SHOWPDFS_H
#define SHOWPDFS_H

#include <QDialog>
#include "user.h"
#include "pdf.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QMessageBox>
#include "homepagefunctions.h"

namespace Ui {
class ShowPdfs;
}

class ShowPdfs : public QDialog
{
    Q_OBJECT

public:
    explicit ShowPdfs(User* user, QWidget *parent = nullptr);
    ~ShowPdfs();

private:
    Ui::ShowPdfs *ui;

    QVBoxLayout* layout = nullptr;
    QWidget* container = nullptr;
    QScrollArea* scrollArea = nullptr;
    void loadPdfs(User* user); // helper method
    User* currentUser;

};

#endif // SHOWPDFS_H
