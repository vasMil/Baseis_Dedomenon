#ifndef ADDCOMPANY_H
#define ADDCOMPANY_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class AddCompany;
}

class AddCompany : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompany(QWidget *parent = nullptr);
    explicit AddCompany(QVariant [], QWidget *parent = nullptr);
    ~AddCompany();

signals:
    void decr_child_count();

    void update_child(QWidget *c);

private slots:

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void fixParent();
    void closeEvent(QCloseEvent *event);
    Ui::AddCompany *ui;
    QWidget *p;
};

#endif // ADDCOMPANY_H
