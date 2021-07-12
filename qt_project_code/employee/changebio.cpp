#include "changebio.h"
#include "ui_changebio.h"

ChangeBio::ChangeBio(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeBio)
{
    ui->setupUi(this);
      connect(this, SIGNAL( fake_click_profile() ), this->parentWidget()->parentWidget()->parentWidget()->parentWidget(), SLOT( on_but_profile_clicked() ) );
}

ChangeBio::~ChangeBio()
{
    delete ui;
}

void ChangeBio::on_buttonBox_accepted()
{
    QString newbio;

        newbio = ui->textEdit->toPlainText();
        if(newbio.isEmpty()){
            QMessageBox::critical(this,"Invalid Bio", "New Bio should not be empty!");
            auto *newch = new ChangeBio(this->parentWidget());
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
            query.prepare("UPDATE employee SET bio = ? WHERE username = ?");
            query.bindValue(0,newbio);
            query.bindValue(1,username);
            if(!query.exec()){
                QMessageBox::critical(this,"Critical Error", "Could not save new password");
                this->close();
            }else{
                QMessageBox::information(this,"Success", "Bio Changed!");
                this->fake_click_profile();
            }
        }


}

void ChangeBio::on_buttonBox_rejected()
{
    QMessageBox::information(this,"Canceled", "Your bio did not change!");
}
