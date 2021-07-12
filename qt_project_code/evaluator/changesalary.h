#ifndef CHANGESALARY_H
#define CHANGESALARY_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangeSalary;
}

class ChangeSalary : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeSalary(QWidget *parent = nullptr);
    explicit ChangeSalary(QString username,QString job_id,QWidget *parent = nullptr);
    ~ChangeSalary();

signals:
    void fake_click_myJobs();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeSalary *ui;
    QString username,job_id;
};

#endif // CHANGESALARY_H
