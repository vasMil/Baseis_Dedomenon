#include "AdminMain.h"
#include "ui_AdminMain.h"

AdminMain::AdminMain(QString username, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::AdminMain)
{
    ui->setupUi(this);
    this->username = username;
    this->setFixedSize(343,517);
    this->child_open = 0;
}

void AdminMain::closeEvent(QCloseEvent *event)
{
    if(child_open != 0){
        centeredMessage(QMessageBox::Warning, "Warning!", "You cannot close main window while a child is still running");
        event->ignore();
    }
}

AdminMain::~AdminMain()
{
    delete ui;
}

void AdminMain::on_pushButton_acc_clicked()
{
    if(this->child_open == 1 && this->child_class == "AddUser"){
        centeredMessage(QMessageBox::Warning, "Warning!", "It seems you have already an AddUser dialog open!");
    }else{
        if(this->child_open == 1){
            this->child->close();
        }
        this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignLeft | Qt::AlignVCenter, this->size(), //center the app after resize
                                              qApp->desktop()->availableGeometry(this)));
        auto *w = new AddUser(this);
        w->setFixedSize(663,517);
        w->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), //center the app after resize
                                           qApp->desktop()->availableGeometry(this)));
        w->show();
        this->child_open++;
        this->child = w;
        this->child_class = "AddUser";
    }
}

void AdminMain::on_pushButton_comp_clicked()
{
    if(this->child_open == 1 && this->child_class == "AddCompany"){
        centeredMessage(QMessageBox::Warning, "Warning!", "It seems you have already an AddCompany dialog open!");
    }else{
        if(this->child_open == 1){
            this->child->close();
        }
        this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignLeft | Qt::AlignVCenter, this->size(), //center the app after resize
                                              qApp->desktop()->availableGeometry(this)));
        auto *w = new AddCompany(this);
        w->setFixedSize(663,517);
        w->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), //center the app after resize
                                           qApp->desktop()->availableGeometry(this)));
        w->show();
        this->child_open++;
        this->child = w;
        this->child_class = "AddCompany";
    }
}

void AdminMain::on_pushButton_subj_clicked()
{
    if(this->child_open == 1 && this->child_class == "AddSubject"){
        centeredMessage(QMessageBox::Warning, "Warning!", "It seems you have already an AddSubject dialog open!");
    }else{
        if(this->child_open == 1){
            this->child->close();
        }
        this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignLeft | Qt::AlignVCenter, this->size(), //center the app after resize
                                              qApp->desktop()->availableGeometry(this)));
        auto *w = new AddSubject(this);
        w->setFixedSize(663,517);
        w->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), //center the app after resize
                                           qApp->desktop()->availableGeometry(this)));
        w->show();
        this->child_open++;
        this->child = w;
        this->child_class = "AddSubject";
    }
}

void AdminMain::on_pushButton_field_clicked()
{
    if(this->child_open == 1 && this->child_class == "AddCompField"){
        centeredMessage(QMessageBox::Warning, "Warning!", "It seems you have already an AddCompField dialog open!");
    }else{
        if(this->child_open == 1){
            this->child->close();
        }
        this->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignLeft | Qt::AlignVCenter, this->size(), //center the app after resize
                                              qApp->desktop()->availableGeometry(this)));
        auto *w = new AddCompField(this);
        w->setFixedSize(663,517);
        w->setGeometry(QStyle::alignedRect(Qt::LeftToRight, Qt::AlignCenter, this->size(), //center the app after resize
                                           qApp->desktop()->availableGeometry(this)));
        w->show();
        this->child_open++;
        this->child = w;
        this->child_class = "AddCompField";
    }
}


void AdminMain::decr_child_count(){
    this->child_open--;
    //qDebug() << this->child_open;
}
void AdminMain::update_child(QWidget *c){
    this->child = c;
    //qDebug() << "New child assigned";
}

void AdminMain::on_actionLogout_triggered()
{
    QSqlQuery query;
    if(!query.exec("SET @usrnm = NULL")){
        qDebug() << "Did not set global variable";
    }
    //close child ->if exists
    if(this->child != nullptr){
        delete this->child;
    }
    this->child_open = 0;
    //close() current window
    close();
    //open login window
    Login *l = new Login;
    //show new window
    l->show();
}

void AdminMain::on_actionExit_triggered()
{
    QSqlQuery query;
    if(!query.exec("SET @usrnm = NULL")){
        qDebug() << "Did not set global variable";
    }
    if(this->child != nullptr){
        delete this->child;
    }
    this->child_open = 0;
    close();
}

/***************************************************************************************************************************************************/
/****************************************************** BUTTON PRESS EFFECT ************************************************************************/
/***************************************************************************************************************************************************/

void AdminMain::on_pushButton_acc_pressed()
{
    ui->pushButton_acc->setStyleSheet("border: 0px; border-radius: 10px; background-color: #A93016; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_acc_released()
{
    ui->pushButton_acc->setStyleSheet("border: 2px solid #A93016; border-radius: 10px; background-color: #000000; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_comp_pressed()
{
    ui->pushButton_comp->setStyleSheet("border: 0px; border-radius: 10px; background-color: #A93016; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_comp_released()
{
    ui->pushButton_comp->setStyleSheet("border: 2px solid #A93016; border-radius: 10px; background-color: #000000; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_field_pressed()
{
    ui->pushButton_field->setStyleSheet("border: 0px; border-radius: 10px; background-color: #A93016; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_field_released()
{
    ui->pushButton_field->setStyleSheet("border: 2px solid #A93016; border-radius: 10px; background-color: #000000; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_subj_pressed()
{
    ui->pushButton_subj->setStyleSheet("border: 0px; border-radius: 10px; background-color: #A93016; font: 12px; color: white; ");
}

void AdminMain::on_pushButton_subj_released()
{
    ui->pushButton_subj->setStyleSheet("border: 2px solid #A93016; border-radius: 10px; background-color: #000000; font: 12px; color: white; ");
}
