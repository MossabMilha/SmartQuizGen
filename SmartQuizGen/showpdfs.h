#ifndef SHOWPDFS_H
#define SHOWPDFS_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QApplication>
#include "user.h"
#include "pdf.h"
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
    User* currentUser;
    QVBoxLayout* layout;
    QWidget* container;

    void loadPdfs(User* user);
};

#endif // SHOWPDFS_H
