#ifndef MANAGERMAIN_H
#define MANAGERMAIN_H

#include <QMainWindow>

namespace Ui {
class ManagerMain;
}

class ManagerMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit ManagerMain(QWidget *parent = nullptr);
    explicit ManagerMain(QString username, QWidget *parent = nullptr);
    ~ManagerMain();

public slots:
        void on_but_myprof_clicked();

private slots:
    //void on_pushButton_clicked();

    void on_but_myprof_pressed();
    void on_but_myprof_released();

    void on_but_comp_clicked();
    void on_but_comp_pressed();
    void on_but_comp_released();

    void on_but_empl_clicked();
    void on_but_empl_pressed();
    void on_but_empl_released();

    void on_but_eval_clicked();
    void on_but_eval_pressed();
    void on_but_eval_released();

    void on_but_res_clicked();
    void on_but_res_pressed();
    void on_but_res_released();

    void on_actionLogout_triggered();

    void on_actionExit_triggered();

    void on_changeSalary_clicked();

private:
    Ui::ManagerMain *ui;
    QString username, company;

    //delete this on exitRoutine (changeSalary updates database on destruction)
    QWidget *openWidget = nullptr;

    //delete any layout that may exist from previous window
    //center the window with the new dimensions
    void prepareForNewWidget();

    //setup the new layout and place inside it the newly created widget
    void setupNewWidget(QWidget*);

    //delete openWidget if it is not null
    //logout from databas (set global variable to NULL)
    //close this window
    void exitRoutine();
};

#endif // MANAGERMAIN_H
