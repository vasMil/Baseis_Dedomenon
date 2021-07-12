#ifndef MANAGEREMPLOYEE_H
#define MANAGEREMPLOYEE_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class ManagerEmployee;
}

class ManagerEmployee : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerEmployee(QWidget *parent = nullptr);
    explicit ManagerEmployee(QString username, QWidget *parent = nullptr);
    ~ManagerEmployee();

private slots:
    void on_but_show_clicked();

    void on_but_update_clicked();

private:
    Ui::ManagerEmployee *ui;
    QWidget* child = nullptr;
};

#endif // MANAGEREMPLOYEE_H
