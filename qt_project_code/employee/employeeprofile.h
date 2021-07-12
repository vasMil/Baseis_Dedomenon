#ifndef EMPLOYEEPROFILE_H
#define EMPLOYEEPROFILE_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class EmployeeProfile;
}

class EmployeeProfile : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeeProfile(QWidget *parent = nullptr);
    explicit EmployeeProfile(QString username, QWidget *parent = nullptr);
    ~EmployeeProfile();

private slots:
    void on_but_chpass_clicked();

    void on_but_chbio_clicked();



    void on_show_button_pressed();
    void on_show_button_released();

private:
    Ui::EmployeeProfile *ui;
};

#endif // EMPLOYEEPROFILE_H
