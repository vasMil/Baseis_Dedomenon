#ifndef LOGIN_H
#define LOGIN_H

#include <QMainWindow>
#include "DBConnect.h"

namespace Ui {
class Login;
}

class Login : public QMainWindow
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

private slots:

    void on_help_clicked();

    void on_login_button_clicked();

    void on_lineEdit_pass_returnPressed();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
