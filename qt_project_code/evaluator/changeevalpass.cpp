#include "changeevalpass.h"
#include "ui_changeevalpass.h"

ChangeEvalPass::ChangeEvalPass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEvalPass)
{
    ui->setupUi(this);

        connect(this, SIGNAL( fake_click_profile() ), this->parentWidget()->parentWidget()->parentWidget()->parentWidget(), SLOT( on_but_profile_clicked() ) );
}


ChangeEvalPass::~ChangeEvalPass()
{
    delete ui;
}

void ChangeEvalPass::on_show_button_pressed()
{

    ui->show_button->setStyleSheet("color: rgb(0, 0, 255); font: bold; background-color: transparent;");
    ui->line_password->setEchoMode(QLineEdit::Normal);
}

void ChangeEvalPass::on_show_button_released()
{

    ui->show_button->setStyleSheet("color: #000000; background-color: transparent;");
        ui->line_password->setEchoMode(QLineEdit::Password);
}

void ChangeEvalPass::on_buttonBox_accepted()
{
    QString newpas;
           newpas = ui->line_password->text();
           if(newpas.isEmpty()){
               QMessageBox::critical(this,"Invalid Password", "New password should not be empty!");
               auto *newch = new ChangeEvalPass(this->parentWidget());
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
               }
               else{
                   QMessageBox::information(this,"Success", "Password Changed!");
                   this->fake_click_profile();
               }
           }
}

void ChangeEvalPass::on_buttonBox_rejected()
{
     QMessageBox::information(this,"Canceled", "Password did not change!");
}
