#include "ManagerProfile.h"
#include "ui_ManagerProfile.h"
#include "DBConnect.h"

ManagerProfile::ManagerProfile(QString username, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ManagerProfile)
{
    ui->setupUi(this);
    QString name, surname, password, email;
    QSqlQuery query;

    query.prepare("CALL getProf(?)");
    query.addBindValue(username);
    if(!query.exec()){
        QMessageBox::critical(this, "Username Error", "Failed to fetch username");
    }

    query.next();
    name = query.value(0).toString();
    surname = query.value(1).toString();
    password = query.value(2).toString();
    email = query.value(3).toString();

    ui->lineEdit_name->setText(name);
    ui->lineEdit_surname->setText(surname);
    ui->lineEdit_username->setText(username);
    ui->lineEdit_password->setText(password);
    ui->lineEdit_email->setText(email);
}

ManagerProfile::~ManagerProfile()
{
    delete ui;
}

void ManagerProfile::on_show_button_pressed()
{
    ui->show_button->setStyleSheet("color: rgb(0, 0, 255); font: bold; background-color: transparent;");
    ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
}

void ManagerProfile::on_show_button_released()
{
    ui->show_button->setStyleSheet("color: #000000; background-color: transparent;");
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

void ManagerProfile::on_but_chpass_clicked()
{
    if(this->child != nullptr){
        this->child->close();
    }
    auto *d = new ChangePassword(this);
    this->child = d;
    d->show();
}

void ManagerProfile::on_but_chemail_clicked()
{
    if(this->child != nullptr){
        this->child->close();
    }
    auto *d = new ChangeEmail(this);
    this->child = d;
    d->show();
}
