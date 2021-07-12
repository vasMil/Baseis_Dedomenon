#ifndef MYJOBS_H
#define MYJOBS_H

#include <QWidget>
#include "DBConnect.h"
namespace Ui {
class MyJobs;
}

class MyJobs : public QWidget
{
    Q_OBJECT

public:
    explicit MyJobs(QWidget *parent = nullptr);
    explicit MyJobs(QString username ,QWidget *parent = nullptr);
    ~MyJobs();

private slots:


    void on_pushButton_salary_clicked();

    void on_pushButton_startDate_clicked();

    void on_pushButton_subDate_clicked();

    void decr_child_count();

    void update_child(QWidget *c);

    void on_comboBox_myjobs_currentIndexChanged(const QString &arg1);

    void on_pushButton_add_clicked();

private:
    Ui::MyJobs *ui;
    QString username,job_id,cur,prev;

     //void closeEvent(QCloseEvent *event);

     QString child_class;
     QWidget *child;
     int child_open;
};

#endif // MYJOBS_H
