#ifndef EMPLOYEEAPPLICATIONS_H
#define EMPLOYEEAPPLICATIONS_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class EmployeeApplications;
}

class EmployeeApplications : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeApplications(QWidget *parent = nullptr);
    explicit EmployeeApplications(QString username, QWidget *parent = nullptr);
    ~EmployeeApplications();

private slots:


    void on_but_del_appl_clicked();


    void on_but_update_appl_clicked();

private:
    Ui::EmployeeApplications *ui;
    QString username;
};

#endif // EMPLOYEEAPPLICATIONS_H
