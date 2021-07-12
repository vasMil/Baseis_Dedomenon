#ifndef MYFOLDER_H
#define MYFOLDER_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class myFolder;
}

class myFolder : public QDialog
{
    Q_OBJECT

public:
    explicit myFolder(QString username, QWidget *parent = nullptr);
    ~myFolder();

signals:
    void fake_click_myFolder();

private slots:
    void on_addnew_deg_clicked();

    void on_addnew_proj_clicked();

    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::myFolder *ui;
    QString username;
    int newDegCount = 0;
};

#endif // MYFOLDER_H
