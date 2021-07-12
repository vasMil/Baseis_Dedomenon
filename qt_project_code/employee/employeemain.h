#ifndef EMPLOYEEMAIN_H
#define EMPLOYEEMAIN_H

#include <QMainWindow>
#include "DBConnect.h"

namespace Ui {
class EmployeeMain;
}

class EmployeeMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit EmployeeMain(QWidget *parent = nullptr);
    explicit EmployeeMain(QString username, QWidget *parent = nullptr);
    ~EmployeeMain();

private slots:
    void on_but_profile_clicked();
    void on_but_profile_pressed();
    void on_but_profile_released();

    void on_but_applications_clicked();
    void on_but_applications_pressed();
    void on_but_applications_released();

    void on_but_myFolder_pressed();
    void on_but_myFolder_released();
    void on_but_myFolder_clicked();

    void on_actionLog_Out_triggered();
    void on_actionExit_triggered();

private:
    Ui::EmployeeMain *ui;
    //
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

#endif // EMPLOYEEMAIN_H
