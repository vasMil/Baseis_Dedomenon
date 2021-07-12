#ifndef CHANGESUBDATE_H
#define CHANGESUBDATE_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangeSubDate;
}

class ChangeSubDate : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeSubDate(QWidget *parent = nullptr);
      explicit ChangeSubDate(QString username, QString job_id,QWidget *parent = nullptr);
    ~ChangeSubDate();

signals:
    void fake_click_myJobs();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::ChangeSubDate *ui;
    QString username,job_id;
};

#endif // CHANGESUBDATE_H
