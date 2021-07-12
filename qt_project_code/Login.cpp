#include "Login.h"
#include "ui_Login.h"

Login::Login(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    QString logo = ":/images/black_login.png";
    QPixmap l(logo);
    ui->login_logo->setPixmap(l);
    logo = ":/images/staff_eval_logo-removebg.png";
    QPixmap p(logo);
    ui->login_button->setIcon(p);
}

Login::~Login()
{
    delete ui;
}

void Login::on_help_clicked()
{
    QMessageBox::information(this, "Help", "Click on staff evaluation logo to login");
}

void Login::on_login_button_clicked()
{
    //get user input into variables
    QVariant username, password;
    username = ui->lineEdit_name->text();
    password = ui->lineEdit_pass->text();
    //check if username and password match
    //if they do match you need to identify the user that logged in as admin, evaluator, manager or employee
    QSqlQuery query;
    query.prepare("CALL verify_user(?, ?)");        //https://stackoverflow.com/questions/13306517/qsqlquery-prepared-select-statement-fails-on-exec
    query.bindValue(0,username);                //do not use QSql::Out, it was not working
    query.bindValue(1,password);
    if (!query.exec()) {
        QMessageBox::critical(this,"Query ERROR","Login query did not execute");
        return;
    }
    query.next();
    int i =  query.value(0).toInt();
                                        //qDebug() << qPrintable(username); //make sure that I am passing the correct values to the
                                        //qDebug() << qPrintable(password);
    if(i == -1){
        QMessageBox::warning(this,"Login Failed!","Username is not valid");
    }
    else if(i == 0){
        QMessageBox::warning(this,"Login Failed!","Password is not correct");
    }
    else if(i == 1){                                            //if admin
        //set the global variable @usrnm to be equal with the users username
        query.prepare("SET @usrnm = ?");
        query.addBindValue(username);
        if(!query.exec()){
            qDebug() << "Did not set global variable";
        }

        //create an instance of admin window
        AdminMain *admin_wind = new AdminMain(username.toString());

        //name the window as Manager - <username>
        admin_wind->QWidget::setWindowTitle("Admin - " + username.toString());

        //show that instance
        admin_wind->show();
        //close the current window
        this->close();
    }
    else if(i == 2){ //if evaluator
        //set the global variable @usrnm to be equal with the users username
        query.prepare("SET @usrnm = ?");
        query.addBindValue(username);
        if(!query.exec()){
            qDebug() << "Did not set global variable";
        }

        //create an instance of admin window
        EvaluatorMain *eval_wind = new EvaluatorMain(username.toString());

        //name the window as Manager - <username>
        eval_wind->QWidget::setWindowTitle("Evaluator - " + username.toString());

        //show that instance
        eval_wind->show();
        //close the current window
        this->close();
    }
    else if(i == 3){                                          //if manager ( aTeRaLit , pos )
        //set the global variable @usrnm to be equal with the users username
        query.prepare("SET @usrnm = ?");
        query.addBindValue(username);
        if(!query.exec()){
            qDebug() << "Did not set global variable";
        }

        //create an instance of manager window
        ManagerMain *manager_wind = new ManagerMain(username.toString());

        //name the window as Manager - <username>
        manager_wind->QWidget::setWindowTitle("Manager - " + username.toString());

        //show the new instance
        manager_wind->show();
        //close the current window
        this->close();
    }
    else if(i == 4){ //if employee
        //set the global variable @usrnm to be equal with the users username
        query.prepare("SET @usrnm = ?");
        query.addBindValue(username);
        if(!query.exec()){
            qDebug() << "Did not set global variable";
        }

        //create an instance of admin window
        EmployeeMain *empl_wind = new EmployeeMain(username.toString());

        //name the window as Manager - <username>
        empl_wind->QWidget::setWindowTitle("Employee - " + username.toString());

        //show that instance
        empl_wind->show();
        //close the current window
        this->close();
    }
    else{
        QMessageBox::critical(this,"Unexpected Error","Unknown state!");
    }
}

void Login::on_lineEdit_pass_returnPressed()
{
    this->on_login_button_clicked();
}
