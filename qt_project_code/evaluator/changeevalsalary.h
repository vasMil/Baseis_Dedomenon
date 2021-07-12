#ifndef CHANGEEVALSALARY_H
#define CHANGEEVALSALARY_H

#include <QDialog>
#include <DBConnect.h>
namespace Ui {
class ChangeEvalSalary;
}

class ChangeEvalSalary : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeEvalSalary(QWidget *parent = nullptr);
     explicit ChangeEvalSalary(QString username,QString job_id,QWidget *parent = nullptr);
    ~ChangeEvalSalary();

signals:
    void fake_click_myJobs();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::ChangeEvalSalary *ui;
    QString username,job_id;
};

#endif // CHANGEEVALSALARY_H
