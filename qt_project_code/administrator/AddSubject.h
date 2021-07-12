#ifndef ADDSUBJECT_H
#define ADDSUBJECT_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class AddSubject;
}

class AddSubject : public QDialog
{
    Q_OBJECT

public:
    explicit AddSubject(QWidget *parent = nullptr);
    explicit AddSubject(QVariant ar[], QWidget *parent);
    ~AddSubject();

signals:
    void decr_child_count();

    void update_child(QWidget *c);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::AddSubject *ui;
    void closeEvent(QCloseEvent *event);
    QWidget *p;
    void fixParent();
};

#endif // ADDSUBJECT_H
