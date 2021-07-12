#ifndef DBCONNECT_H
#define DBCONNECT_H

/*QT INCLUDES*/
#include <QMainWindow>
#include <QMessageBox>
#include <QtSql>
#include <QSqlDatabase>
#include <QLabel>
#include <QPixmap>
#include <QSqlQuery>
#include <QStyle>
#include <QDesktopWidget>
#include <QtWidgets>
#include <QComboBox>
#include <QPalette>
#include <QCloseEvent>
#include <QMetaType>
#include <QGuiApplication>

/*MANAGER INCLUDES*/
#include "ManagerMain.h"
#include "Login.h"
#include "ManagerProfile.h"
#include "ChangePassword.h"
#include "ChangeEmail.h"
#include "ManagerCompany.h"
#include "ManagerEmployee.h"
#include "EmployeeCertificates.h"
#include "ChangeSalary.h"
#include "EvaluatorAverage.h"
#include "ManagerResult.h"

/*My headers*/
#include "myQt_Functions.h"

/*ADMINISTRATOR INCLUDES*/
#include "AdminMain.h"
#include "AddUser.h"
#include "AddCompany.h"
#include "AddSubject.h"
#include "AddCompField.h"

/*EVALUATOR INCLUDES*/
#include "Login.h"
#include "evaluatormain.h"
#include "evaluatorprofile.h"
#include "changeevalpass.h"
#include "evaluatorjobs.h"
#include "myjobs.h"
#include "changeevalemail.h"
#include "evalresults.h"
#include "changestartdate.h"
#include "changesubdate.h"
#include "addjobs.h"
#include "changeevalsalary.h"
#include "MyResultsEval.h"

/*EMPLOYEE INCLUDES*/
#include "changebio.h"
#include "changeemplpass.h"
#include "deleteapplications.h"
#include "employeeapplications.h"
#include "employeemain.h"
#include "employeeprofile.h"
#include "updateapplications.h"
#include "myFolder.h"

namespace Ui {
class DBConnect;
}

class DBConnect : public QMainWindow
{
    Q_OBJECT

public:
    explicit DBConnect(QWidget *parent = nullptr);
    ~DBConnect();

private slots:
    void on_pushButton_clicked();
    void on_toolButton_clicked();

private:
    Ui::DBConnect *ui;
};

#endif // DBCONNECT_H
