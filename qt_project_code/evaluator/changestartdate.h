#ifndef CHANGESTARTDATE_H
#define CHANGESTARTDATE_H

#include <QDialog>
#include "DBConnect.h"
#include <QDate>
namespace Ui {
class ChangeStartDate;
}

class ChangeStartDate : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeStartDate(QWidget *parent = nullptr);
    explicit ChangeStartDate(QString username, QString job_id ,QWidget *parent = nullptr);
    ~ChangeStartDate();

signals:
    void fake_click_myJobs();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeStartDate *ui;
    QString username, job_id;
};

#endif // CHANGESTARTDATE_H
