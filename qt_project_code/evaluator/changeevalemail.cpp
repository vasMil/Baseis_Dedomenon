#include "changeevalemail.h"
#include "ui_changeevalemail.h"

ChangeEvalEmail::ChangeEvalEmail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeEvalEmail)
{
    ui->setupUi(this);
    connect(this, SIGNAL( fake_click_profile() ), this->parentWidget()->parentWidget()->parentWidget()->parentWidget(), SLOT( on_but_profile_clicked() ) );
}

ChangeEvalEmail::~ChangeEvalEmail()
{
    delete ui;
}

void ChangeEvalEmail::on_buttonBox_accepted()
{
    QString newmail;
        newmail = ui->email->text();
        bool like = 0; int i = 0;
        while(i < newmail.length()){
            if(newmail[i] == '@' && i > 0){
                like = 1;
                break;
            }
            i++;
        }
        if(newmail.isEmpty() || !like){
            QMessageBox::critical(this,"Invalid Email", "New email should be like: \n'some_user'@'some_org'");
            auto *newch = new ChangeEvalEmail(this->parentWidget());
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
            query.prepare("UPDATE user SET email = ? WHERE username = ?");
            query.bindValue(0,newmail);
            query.bindValue(1,username);
            if(!query.exec()){
                QMessageBox::critical(this,"Critical Error", "Could not save new email");
                this->close();
            }else{
                QMessageBox::information(this,"Success", "Email Changed!");
                this->fake_click_profile();
            }
        }

}

void ChangeEvalEmail::on_buttonBox_rejected()
{
     QMessageBox::information(this,"Canceled", "Your email did not change!");
}
