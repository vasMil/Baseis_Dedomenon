#ifndef CHANGESALARY_H
#define CHANGESALARY_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class ChangeSalary;
}

class ChangeSalary : public QWidget
{
    Q_OBJECT

public:
    explicit ChangeSalary(QWidget *parent = nullptr);
    explicit ChangeSalary(QString afm, QWidget *parent = nullptr);
    ~ChangeSalary();

private:
    Ui::ChangeSalary *ui;
    QString afm;
};

#endif // CHANGESALARY_H
