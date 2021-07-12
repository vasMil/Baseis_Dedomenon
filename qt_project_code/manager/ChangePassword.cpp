#include "ChangePassword.h"
#include "ui_ChangePassword.h"

ChangePassword::ChangePassword(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangePassword)
{
    ui->setupUi(this);
    connect(this, SIGNAL( fake_click_myprof() ), this->parentWidget()->parentWidget()->parentWidget()
            ->parentWidget(), SLOT( on_but_myprof_clicked() ) );
}

ChangePassword::~ChangePassword()
{
    delete ui;
}

void ChangePassword::on_buttonBox_accepted()
{
    QString newpas;
    newpas = ui->password->text();
    if(newpas.isEmpty()){
        QMessageBox::critical(this,"Invalid Password", "New password should not be empty!");
        auto *newch = new ChangePassword(this->parentWidget());
        newch->show();
        this->close();
    } else{
        QString username;
        QSqlQuery query;
        query.prepare("SELECT @usrnm");
        if(!query.exec()){
            QMessageBox::critical(this,"Critical Error", "Could not fetch username");
            this->close();
        }
        query.next();
        username = query.value(0).toString();
        query.clear();
        if(username.isEmpty()){
            QMessageBox::critical(this,"Critical Error", "Could not fetch username is empty");
            this->close();
        }
        query.prepare("UPDATE user SET password = ? WHERE username = ?");
        query.bindValue(0,newpas);
        query.bindValue(1,username);
        if(!query.exec()){
            QMessageBox::critical(this,"Critical Error", "Could not save new password");
            this->close();
        }else{
            QMessageBox::information(this,"Success", "Password Changed!");
            fake_click_myprof();
        }
    }
}

void ChangePassword::on_buttonBox_rejected()
{
    QMessageBox::information(this,"Canceled", "Password did not change!");
}

void ChangePassword::on_show_button_pressed()
{
    ui->show_button->setStyleSheet("color: rgb(0, 0, 255); font: bold; background-color: transparent;");
    ui->password->setEchoMode(QLineEdit::Normal);
}

void ChangePassword::on_show_button_released()
{
    ui->show_button->setStyleSheet("color: #000000; background-color: transparent;");
    ui->password->setEchoMode(QLineEdit::Password);
}
