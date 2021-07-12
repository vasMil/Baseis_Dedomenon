#ifndef CHANGEPASSWORD_H
#define CHANGEPASSWORD_H

#include <QDialog>
#include "DBConnect.h"

namespace Ui {
class ChangePassword;
}

class ChangePassword : public QDialog
{
    Q_OBJECT

public:
    explicit ChangePassword(QWidget *parent = nullptr);
    ~ChangePassword();

signals:
    void fake_click_myprof();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_show_button_pressed();

    void on_show_button_released();

private:
    Ui::ChangePassword *ui;
};

#endif // CHANGEPASSWORD_H
