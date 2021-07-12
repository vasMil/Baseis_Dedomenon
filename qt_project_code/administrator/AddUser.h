#ifndef ADDUSER_H
#define ADDUSER_H

#include <QDialog>

namespace Ui {
class AddUser;
}

class AddUser : public QDialog
{
    Q_OBJECT

public:
    explicit AddUser(QWidget *parent = nullptr);
    explicit AddUser(QVariant ar[], QWidget *parent = nullptr);
    ~AddUser();

signals:
    void decr_child_count();

    void update_child(QWidget *c);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    void fixParent();
    void closeEvent(QCloseEvent *event);
    Ui::AddUser *ui;
    QWidget *p;
};

#endif // ADDUSER_H
