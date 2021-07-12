#include "employeeprofile.h"
#include "ui_employeeprofile.h"

EmployeeProfile::EmployeeProfile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeProfile)
{
    ui->setupUi(this);
}
EmployeeProfile::EmployeeProfile(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EmployeeProfile)
{

              ui->setupUi(this);

           QString name, surname, password, bio;
           QSqlQuery query;

           query.prepare("CALL getEmplProf(?)");
           query.bindValue(0, username);
           if(!query.exec()){
               QMessageBox::critical(this, "Username Error", "Failed to fetch username");
           }
           query.next();
           name = query.value(0).toString();
           surname = query.value(1).toString();
           password = query.value(2).toString();
           bio = query.value(3).toString();

           ui->lineEdit_name->setText(name);
           ui->lineEdit_surname->setText(surname);
           ui->lineEdit_username->setText(username);
           ui->lineEdit_password->setText(password);
           ui->textEdit->setText(bio);
}


EmployeeProfile::~EmployeeProfile()
{
    delete ui;
}

void EmployeeProfile::on_but_chpass_clicked()
{
    auto *d = new ChangeEmplPass(this);
       d->show();
}

void EmployeeProfile::on_but_chbio_clicked()
{
    auto *d = new ChangeBio(this);
        d->show();
}



void EmployeeProfile::on_show_button_pressed()
{

    ui->show_button->setStyleSheet("color: rgb(0, 0, 255); font: bold; background-color: transparent;");
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
}

void EmployeeProfile::on_show_button_released()
{
    ui->show_button->setStyleSheet("color: #000000; background-color: transparent;");
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}
