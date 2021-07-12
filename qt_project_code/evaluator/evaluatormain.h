#ifndef EVALUATORMAIN_H
#define EVALUATORMAIN_H

#include <QMainWindow>
#include "DBConnect.h"
namespace Ui {
class EvaluatorMain;
}

class EvaluatorMain : public QMainWindow
{
    Q_OBJECT

public:
    explicit EvaluatorMain(QWidget *parent = nullptr);
     explicit EvaluatorMain(QString username, QWidget *parent = nullptr);
    ~EvaluatorMain();

private slots:
    void on_actionLog_Out_triggered();
    void on_actionExit_triggered();

    void on_but_profile_clicked();
    void on_but_profile_pressed();
    void on_but_profile_released();

    void on_but_jobs_clicked();
    void on_but_jobs_pressed();
    void on_but_jobs_released();



    void on_but_myJobs_released();
    void on_but_myJobs_clicked();
    void on_but_myJobs_pressed();



    void on_but_results_pressed();

    void on_but_results_released();

    void on_but_results_clicked();



    void on_but_myResults_pressed();

    void on_but_myResults_released();

    void on_but_myResults_clicked();

private:
    Ui::EvaluatorMain *ui;
    QString username;
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

#endif // EVALUATORMAIN_H
