#ifndef MANAGERRESULT_H
#define MANAGERRESULT_H

#include <QWidget>
#include "DBConnect.h"

namespace Ui {
class ManagerResult;
}

class ManagerResult : public QWidget
{
    Q_OBJECT

public:
    explicit ManagerResult(QWidget *parent = nullptr);
    explicit ManagerResult(QString afm, QWidget *parent = nullptr);
    ~ManagerResult();

private:
    Ui::ManagerResult *ui;
};

#endif // MANAGERRESULT_H
