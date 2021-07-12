#ifndef ADDCOMPFIELD_H
#define ADDCOMPFIELD_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class AddCompField;
}

class AddCompField : public QDialog
{
    Q_OBJECT

public:
    explicit AddCompField(QWidget *parent = nullptr);
    ~AddCompField();

private slots:
    void on_pushButton_add_clicked();

    void on_pushButton_create_clicked();

signals:
    void decr_child_count();

private:
    Ui::AddCompField *ui;
    QWidget *p;
    void add_action(QString title, QString descr);
    void add_action_to_comp(QString afm, QString newfield);
    void closeEvent(QCloseEvent *event);
};

#endif // ADDCOMPFIELD_H
