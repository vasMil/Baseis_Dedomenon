#ifndef ADMINMAIN_H
#define ADMINMAIN_H

#include <QMainWindow>
#include "DBConnect.h"

namespace Ui {
class AdminMain;
}

class AdminMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit AdminMain(QWidget *parent = nullptr);
    explicit AdminMain(QString username, QWidget *parent = nullptr);
    ~AdminMain();

private slots:
    void on_pushButton_acc_clicked();

    void on_pushButton_comp_clicked();

    void on_pushButton_subj_clicked();

    void decr_child_count();

    void update_child(QWidget *c);

    void on_pushButton_field_clicked();

    void on_actionLogout_triggered();

    void on_actionExit_triggered();

/*********************************** BUTTON PRESS EFFECT ***************************************/

    void on_pushButton_acc_pressed();

    void on_pushButton_acc_released();

    void on_pushButton_comp_pressed();

    void on_pushButton_comp_released();

    void on_pushButton_field_pressed();

    void on_pushButton_field_released();

    void on_pushButton_subj_pressed();

    void on_pushButton_subj_released();

/*********************************** END - BUTTON PRESS EFFECT ***************************************/

private:
    Ui::AdminMain *ui;
    void closeEvent(QCloseEvent *event);
    QString username;
    QString child_class;
    QWidget *child = nullptr;
    int child_open;
};

#endif // ADMINMAIN_H
