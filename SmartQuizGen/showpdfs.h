#ifndef SHOWPDFS_H
#define SHOWPDFS_H

#include <QDialog>
#include "user.h"

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

};

#endif // SHOWPDFS_H
