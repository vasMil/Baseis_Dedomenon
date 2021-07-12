#ifndef EMPLOYEECERTIFICATES_H
#define EMPLOYEECERTIFICATES_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class EmployeeCertificates;
}

class EmployeeCertificates : public QDialog
{
    Q_OBJECT

public:
    explicit EmployeeCertificates(QWidget *parent = nullptr);
    explicit EmployeeCertificates(QString empl, QWidget *parent = nullptr);
    ~EmployeeCertificates();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EmployeeCertificates *ui;
    QString empl;
    QString username;
    bool has_report = 0; //by default assume that the manager does not have a report for the employee
};


#endif // EMPLOYEECERTIFICATES_H
